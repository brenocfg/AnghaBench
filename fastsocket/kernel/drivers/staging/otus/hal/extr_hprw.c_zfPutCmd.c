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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int u16_t ;
struct zsHpPriv {int cmdTail; int cmdHead; TYPE_1__* cmdQ; } ;
struct TYPE_4__ {struct zsHpPriv* hpPrivate; } ;
struct TYPE_3__ {int cmdLen; int src; int /*<<< orphan*/ * cmd; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int ZM_CMD_QUEUE_SIZE ; 
 int ZM_MAX_CMD_SIZE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfPutCmd(zdev_t* dev, u32_t* cmd, u16_t cmdLen, u16_t src, u8_t* buf)
{
    u16_t i;
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;

    /* Make sure command length < ZM_MAX_CMD_SIZE */
    zm_assert(cmdLen <= ZM_MAX_CMD_SIZE);
    /* Make sure command queue not full */
    //zm_assert(((hpPriv->cmdTail+1) & (ZM_CMD_QUEUE_SIZE-1)) != hpPriv->cmdHead);
    if (((hpPriv->cmdTail+1) & (ZM_CMD_QUEUE_SIZE-1)) == hpPriv->cmdHead ) {
        zm_debug_msg0("CMD queue full!!");
        return 0;
    }

    hpPriv->cmdQ[hpPriv->cmdTail].cmdLen = cmdLen;
    hpPriv->cmdQ[hpPriv->cmdTail].src = src;
    hpPriv->cmdQ[hpPriv->cmdTail].buf = buf;
    for (i=0; i<(cmdLen>>2); i++)
    {
        hpPriv->cmdQ[hpPriv->cmdTail].cmd[i] = cmd[i];
    }

    hpPriv->cmdTail = (hpPriv->cmdTail+1) & (ZM_CMD_QUEUE_SIZE-1);

    return 0;
}