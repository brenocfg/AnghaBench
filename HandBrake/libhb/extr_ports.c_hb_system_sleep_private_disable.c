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
typedef  scalar_t__ IOReturn ;
typedef  int IOPMAssertionID ;
typedef  int /*<<< orphan*/  CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFSTR (char*) ; 
 scalar_t__ IOPMAssertionCreateWithName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*,int) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  kIOPMAssertPreventUserIdleSystemSleep ; 
 int /*<<< orphan*/  kIOPMAssertionLevelOn ; 
 scalar_t__ kIOReturnSuccess ; 

void hb_system_sleep_private_disable(void *opaque)
{
#ifdef __APPLE__
    if (opaque == NULL)
    {
        hb_error("hb_system_sleep: opaque is NULL");
        return;
    }

    IOPMAssertionID *assertionID = (IOPMAssertionID*)opaque;
    if (*assertionID != -1)
    {
        // nothing to do
        return;
    }

    // 128 chars limit for IOPMAssertionCreateWithName
    CFStringRef reasonForActivity =
    CFSTR("HandBrake is currently scanning and/or encoding");

    IOReturn success = IOPMAssertionCreateWithName(kIOPMAssertPreventUserIdleSystemSleep,
                                                   kIOPMAssertionLevelOn,
                                                   reasonForActivity,
                                                   assertionID);
    if (success == kIOReturnSuccess)
    {
        hb_deep_log(3,
                    "hb_system_sleep: assertion %d created, sleep prevented",
                    *assertionID);
    }
    else
    {
        hb_log("hb_system_sleep: failed to prevent system sleep");
    }
#endif
}