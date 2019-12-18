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
struct TYPE_3__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ iohidmanager_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFRunLoopGetCurrent () ; 
 scalar_t__ IOHIDManagerCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOHIDManagerScheduleWithRunLoop (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOHIDManagerSetDeviceMatching (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFRunLoopDefaultMode ; 
 int /*<<< orphan*/  kIOHIDOptionsTypeNone ; 

__attribute__((used)) static int iohidmanager_hid_manager_init(iohidmanager_hid_t *hid)
{
   if (!hid)
      return -1;
   if (hid->ptr) /* already initialized. */
      return 0;

   hid->ptr = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);

   if (!hid->ptr)
      return -1;

   IOHIDManagerSetDeviceMatching(hid->ptr, NULL);
   IOHIDManagerScheduleWithRunLoop(hid->ptr, CFRunLoopGetCurrent(),
         kCFRunLoopDefaultMode);
   return 0;
}