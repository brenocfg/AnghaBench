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
struct snd_usb_substream {int /*<<< orphan*/  sync_endpoint; int /*<<< orphan*/  data_endpoint; int /*<<< orphan*/  altset_idx; int /*<<< orphan*/  interface; scalar_t__ running; } ;
struct snd_info_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_dump_ep_status (struct snd_usb_substream*,int /*<<< orphan*/ ,struct snd_info_buffer*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void proc_dump_substream_status(struct snd_usb_substream *subs, struct snd_info_buffer *buffer)
{
	if (subs->running) {
		snd_iprintf(buffer, "  Status: Running\n");
		snd_iprintf(buffer, "    Interface = %d\n", subs->interface);
		snd_iprintf(buffer, "    Altset = %d\n", subs->altset_idx);
		proc_dump_ep_status(subs, subs->data_endpoint, buffer);
		proc_dump_ep_status(subs, subs->sync_endpoint, buffer);
	} else {
		snd_iprintf(buffer, "  Status: Stop\n");
	}
}