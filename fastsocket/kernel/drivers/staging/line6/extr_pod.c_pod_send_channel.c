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
struct usb_line6_pod {int channel_num; int /*<<< orphan*/  dumpreq; int /*<<< orphan*/  line6; } ;

/* Variables and functions */
 int /*<<< orphan*/  line6_dump_finished (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line6_invalidate_current (int /*<<< orphan*/ *) ; 
 scalar_t__ line6_send_program (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pod_send_channel(struct usb_line6_pod *pod, int value)
{
	line6_invalidate_current(&pod->dumpreq);

	if (line6_send_program(&pod->line6, value) == 0)
		pod->channel_num = value;
	else
		line6_dump_finished(&pod->dumpreq);
}