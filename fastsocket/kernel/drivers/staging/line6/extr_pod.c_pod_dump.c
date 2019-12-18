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
struct usb_line6_pod {char prog_data; int /*<<< orphan*/  line6; } ;

/* Variables and functions */
 int /*<<< orphan*/  POD_SYSEX_DUMP ; 
 size_t SYSEX_DATA_OFS ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  line6_send_sysex_message (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,int) ; 
 char* pod_alloc_sysex_buffer (struct usb_line6_pod*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pod_mark_batch_all_dirty (struct usb_line6_pod*) ; 

__attribute__((used)) static void pod_dump(struct usb_line6_pod *pod, const unsigned char *data)
{
	int size = 1 + sizeof(pod->prog_data);
	char *sysex = pod_alloc_sysex_buffer(pod, POD_SYSEX_DUMP, size);
	if (!sysex)
		return;
	/* Don't know what this is good for, but PODxt Pro transmits it, so we
	 * also do... */
	sysex[SYSEX_DATA_OFS] = 5;
	memcpy(sysex + SYSEX_DATA_OFS + 1, data, sizeof(pod->prog_data));
	line6_send_sysex_message(&pod->line6, sysex, size);
	memcpy(&pod->prog_data, data, sizeof(pod->prog_data));
	pod_mark_batch_all_dirty(pod);
	kfree(sysex);
}