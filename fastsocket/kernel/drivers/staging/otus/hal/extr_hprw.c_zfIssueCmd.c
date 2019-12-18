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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  scalar_t__ u16_t ;
struct zsHpPriv {int cmdPending; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_1 ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfIdlCmd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zfPutCmd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfSendCmdEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_msg2_mm (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfIssueCmd(zdev_t* dev, u32_t* cmd, u16_t cmdLen, u16_t src, u8_t* buf)
{
    u16_t cmdFlag = 0;
    u16_t ret;
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;

    zmw_declare_for_critical_section();

    zm_msg2_mm(ZM_LV_1, "cmdLen=", cmdLen);

    zmw_enter_critical_section(dev);

#ifdef ZM_XP_USB_MULTCMD
    ret = zfPutCmd(dev, cmd, cmdLen, src, buf);
    zmw_leave_critical_section(dev);

    if (ret != 0)
    {
        return 1;
    }

    zfSendCmdEx(dev);
#else
    if (hpPriv->cmdPending == 0)
    {
        hpPriv->cmdPending = 1;
        cmdFlag = 1;
    }
    ret = zfPutCmd(dev, cmd, cmdLen, src, buf);

    zmw_leave_critical_section(dev);

    if (ret != 0)
    {
        return 1;
    }

    if (cmdFlag == 1)
    {
        zfIdlCmd(dev, cmd, cmdLen);
    }
#endif
    return 0;
}