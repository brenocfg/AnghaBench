#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
struct TYPE_2__ {int queueFlushed; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/ * zfGetVmmq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfGetVtxq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfFlushVtxq(zdev_t* dev)
{
    zbuf_t* buf;
    u8_t i;
    zmw_get_wlan_dev(dev);

    /* Flush MmQ */
    while ((buf = zfGetVmmq(dev)) != 0)
    {
        zfwBufFree(dev, buf, 0);
        zm_debug_msg0("zfFlushVtxq: [Vmmq]");
        wd->queueFlushed  |= 0x10;
    }

    /* Flush VTxQ */
    for (i=0; i<4; i++)
    {
        while ((buf = zfGetVtxq(dev, i)) != 0)
        {
            zfwBufFree(dev, buf, 0);
            zm_debug_msg1("zfFlushVtxq: [zfGetVtxq]- ", i);
            wd->queueFlushed |= (1<<i);
        }
    }
}