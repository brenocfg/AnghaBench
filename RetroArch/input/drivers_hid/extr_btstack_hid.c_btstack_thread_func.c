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
struct TYPE_3__ {int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ CFRunLoopSourceContext ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRunLoopAddSource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRunLoopGetCurrent () ; 
 int /*<<< orphan*/  CFRunLoopRun () ; 
 int /*<<< orphan*/  CFRunLoopSourceCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CFRunLoopSourceInvalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_POWER_ON ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 scalar_t__ bt_open_ptr () ; 
 int /*<<< orphan*/  bt_send_cmd_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btstack_quit_source ; 
 int /*<<< orphan*/  btstack_set_power_mode_ptr ; 
 int /*<<< orphan*/  btstack_thread_stop ; 
 int /*<<< orphan*/  kCFRunLoopCommonModes ; 

__attribute__((used)) static void btstack_thread_func(void* data)
{
   RARCH_LOG("[BTstack]: Thread started");

   if (bt_open_ptr())
      return;

#ifdef __APPLE__
   CFRunLoopSourceContext ctx = { 0, 0, 0, 0, 0, 0, 0, 0, 0, btstack_thread_stop };
   btstack_quit_source = CFRunLoopSourceCreate(0, 0, &ctx);
   CFRunLoopAddSource(CFRunLoopGetCurrent(), btstack_quit_source, kCFRunLoopCommonModes);
#endif

   RARCH_LOG("[BTstack]: Turning on...\n");
   bt_send_cmd_ptr(btstack_set_power_mode_ptr, HCI_POWER_ON);

   RARCH_LOG("BTstack: Thread running...\n");
#ifdef __APPLE__
   CFRunLoopRun();
#endif

   RARCH_LOG("[BTstack]: Thread done.\n");

#ifdef __APPLE__
   CFRunLoopSourceInvalidate(btstack_quit_source);
   CFRelease(btstack_quit_source);
#endif
}