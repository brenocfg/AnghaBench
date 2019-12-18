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
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 int ZM_SUCCESS ; 
 int zfHpSend (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfwBufRemoveHead (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zmw_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfiTxSend80211Mgmt(zdev_t* dev, zbuf_t* buf, u16_t port)
{
    u16_t err;
    //u16_t addrTblSize = 0;
    //struct zsAddrTbl addrTbl;
    u16_t hlen;
    u16_t header[(24+25+1)/2];
    int i;

    for(i=0;i<12;i++)
    {
        header[i] = zmw_buf_readh(dev, buf, i);
    }
    hlen = 24;

    zfwBufRemoveHead(dev, buf, 24);

    if ((err = zfHpSend(dev, header, hlen, NULL, 0, NULL, 0, buf, 0,
            ZM_EXTERNAL_ALLOC_BUF, 0, 0)) != ZM_SUCCESS)
    {
        goto zlError;
    }

    return 0;

zlError:

    zfwBufFree(dev, buf, 0);
    return 0;
}