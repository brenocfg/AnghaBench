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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */
 int cpu_to_le16 (int) ; 
 int zfLnxUsbOut (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

u32_t zfwUsbSend(zdev_t* dev, u8_t endpt, u8_t *hdr, u16_t hdrlen, u8_t *snap, u16_t snapLen,
                u8_t *tail, u16_t tailLen, zbuf_t *buf, u16_t offset)
{
    u32_t status;

#ifdef ZM_CONFIG_BIG_ENDIAN
    u32_t ii = 0;
    u16_t *pc = NULL;

    pc = (u16_t *)hdr;
    for(ii=0; ii<(hdrlen>>1); ii++)
    {
        pc[ii] = cpu_to_le16(pc[ii]);
    }

    pc = (u16_t *)snap;
    for(ii=0; ii<(snapLen>>1); ii++)
    {
        pc[ii] = cpu_to_le16(pc[ii]);
    }

    pc = (u16_t *)tail;
    for(ii=0; ii<(tailLen>>1); ii++)
    {
        pc[ii] = cpu_to_le16(pc[ii]);
    }
#endif

    status = zfLnxUsbOut(dev, hdr, hdrlen, snap, snapLen, tail, tailLen, buf, offset);
    if ( status == 0 )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}