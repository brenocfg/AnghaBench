#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ iohidmanager_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRunLoopGetCurrent () ; 
 int /*<<< orphan*/  IOHIDManagerClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOHIDManagerUnscheduleFromRunLoop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFRunLoopCommonModes ; 
 int /*<<< orphan*/  kIOHIDOptionsTypeNone ; 

__attribute__((used)) static int iohidmanager_hid_manager_free(iohidmanager_hid_t *hid)
{
   if (!hid || !hid->ptr)
      return -1;

   IOHIDManagerUnscheduleFromRunLoop(hid->ptr,
         CFRunLoopGetCurrent(), kCFRunLoopCommonModes);
   IOHIDManagerClose(hid->ptr, kIOHIDOptionsTypeNone);
   CFRelease(hid->ptr);
   hid->ptr = NULL;

   return 0;
}