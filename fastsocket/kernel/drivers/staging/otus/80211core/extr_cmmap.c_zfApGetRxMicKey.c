#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct zsMicVar {int dummy; } ;
struct TYPE_5__ {TYPE_1__* staTable; } ;
struct TYPE_6__ {TYPE_2__ ap; } ;
struct TYPE_4__ {struct zsMicVar rxMicKey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_WLAN_HEADER_A2_OFFSET ; 
 TYPE_3__* wd ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfCopyFromRxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

struct zsMicVar* zfApGetRxMicKey(zdev_t* dev, zbuf_t* buf)
{
    u8_t sa[6];
    u16_t id = 0, macAddr[3];

    zmw_get_wlan_dev(dev);

    zfCopyFromRxBuffer(dev, buf, sa, ZM_WLAN_HEADER_A2_OFFSET, 6);

    macAddr[0] = sa[0] + (sa[1] << 8);
    macAddr[1] = sa[2] + (sa[3] << 8);
    macAddr[2] = sa[4] + (sa[5] << 8);

    if ((id = zfApFindSta(dev, macAddr)) != 0xffff)
        return (&wd->ap.staTable[id].rxMicKey);

    return NULL;
}