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
struct TYPE_5__ {TYPE_1__* staTable; struct zsMicVar* bcMicKey; } ;
struct TYPE_6__ {TYPE_2__ ap; } ;
struct TYPE_4__ {int qosType; struct zsMicVar txMicKey; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfCopyFromIntTxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

struct zsMicVar* zfApGetTxMicKey(zdev_t* dev, zbuf_t* buf, u8_t* qosType)
{
    u8_t da[6];
    u16_t id = 0, macAddr[3];

    zmw_get_wlan_dev(dev);

    zfCopyFromIntTxBuffer(dev, buf, da, 0, 6);

    macAddr[0] = da[0] + (da[1] << 8);
    macAddr[1] = da[2] + (da[3] << 8);
    macAddr[2] = da[4] + (da[5] << 8);

    if ((macAddr[0] & 0x1))
    {
        return (&wd->ap.bcMicKey[0]);
    }
    else if ((id = zfApFindSta(dev, macAddr)) != 0xffff)
    {
        *qosType = wd->ap.staTable[id].qosType;
        return (&wd->ap.staTable[id].txMicKey);
    }

    return NULL;
}