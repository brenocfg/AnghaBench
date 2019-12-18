#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfShowTxEAPOL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zmw_tx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfTxGenWlanSnap(zdev_t* dev, zbuf_t* buf, u16_t* snap, u16_t* snaplen)
{
    u16_t removed;
	   u16_t etherType;
   	u16_t len;

	   len = zfwBufGetSize(dev, buf);
    if (len < 14) //Minimum Ethernet packet size, 14(Ether header)
    {
        /* TODO : Assert? */
        *snaplen = 0;
        return 0;
    }

    /* Generate RFC1042 header */
    etherType = (((u16_t)zmw_tx_buf_readb(dev, buf, 12))<<8)
                + zmw_tx_buf_readb(dev, buf, 13);

    //zm_debug_msg2("ethernet type or length = ", etherType);

    if (etherType > 1500)
    {
        /* ETHERNET format */
        removed = 12;
        snap[0] = 0xaaaa;
        snap[1] = 0x0003;
        if ((etherType ==0x8137) || (etherType == 0x80f3))
        {
            /* Bridge Tunnel */
            snap[2] = 0xF800;
        }
        else
        {
            /* RFC 1042 */
            snap[2] = 0x0000;
        }
        *snaplen = 6;

        if ( etherType == 0x888E )
        {
            zfShowTxEAPOL(dev, buf, 14);
        }
    }
    else
    {
        /* 802.3 format */
        removed = 14;
        *snaplen = 0;
    }

    return removed;
}