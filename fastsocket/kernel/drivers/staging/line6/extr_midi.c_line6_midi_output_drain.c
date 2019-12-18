#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct usb_line6 {TYPE_1__* line6midi; } ;
struct snd_rawmidi_substream {int dummy; } ;
struct TYPE_8__ {struct usb_line6* line6; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct TYPE_6__ {scalar_t__ num_active_send_urbs; int /*<<< orphan*/  send_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 TYPE_3__* line6_rawmidi_substream_midi (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void line6_midi_output_drain(struct snd_rawmidi_substream *substream)
{
	struct usb_line6 *line6 = line6_rawmidi_substream_midi(substream)->line6;
	wait_queue_head_t *head = &line6->line6midi->send_wait;
	DECLARE_WAITQUEUE(wait, current);
	add_wait_queue(head, &wait);
	current->state = TASK_INTERRUPTIBLE;

	while (line6->line6midi->num_active_send_urbs > 0)
		if (signal_pending(current))
			break;
		else
			schedule();

	current->state = TASK_RUNNING;
	remove_wait_queue(head, &wait);
}