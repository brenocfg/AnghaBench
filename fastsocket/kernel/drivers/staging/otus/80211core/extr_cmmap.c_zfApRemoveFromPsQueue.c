#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {int uniTail; int /*<<< orphan*/ * uniArray; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;

/* Variables and functions */
 int ZM_UNI_ARRAY_SIZE ; 
 TYPE_2__* wd ; 
 int zmw_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfApRemoveFromPsQueue(zdev_t* dev, u16_t id, u16_t* addr)
{
    u16_t dst[3];
    u16_t nid;
    u8_t moreData = 0;
    zmw_get_wlan_dev(dev);

    wd->ap.uniTail = (wd->ap.uniTail-1) & (ZM_UNI_ARRAY_SIZE-1);
    while (id != wd->ap.uniTail)
    {
        nid = (id + 1) & (ZM_UNI_ARRAY_SIZE - 1);
        wd->ap.uniArray[id] = wd->ap.uniArray[nid];

        /* Search until tail to config more data bit */
        dst[0] = zmw_buf_readh(dev, wd->ap.uniArray[id], 0);
        dst[1] = zmw_buf_readh(dev, wd->ap.uniArray[id], 2);
        dst[2] = zmw_buf_readh(dev, wd->ap.uniArray[id], 4);
        if ((addr[0] == dst[0]) && (addr[1] == dst[1])
                && (addr[2] == dst[2]))
        {
            moreData = 0x20;
        }

        id = nid;
    }
    return moreData;
}