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
struct snd_seq_event {int dummy; } ;

/* Variables and functions */
 int snd_seq_control_queue (struct snd_seq_event*,int,int) ; 

__attribute__((used)) static int event_input_timer(struct snd_seq_event * ev, int direct, void *private_data, int atomic, int hop)
{
	return snd_seq_control_queue(ev, atomic, hop);
}