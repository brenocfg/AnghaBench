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
struct usb_line6_pod {int /*<<< orphan*/  dumpreq; int /*<<< orphan*/  line6; } ;
struct usb_interface {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  POD_DUMP_MEMORY ; 
 int /*<<< orphan*/  POD_SYSEX_DUMPMEM ; 
 int SYSEX_DATA_OFS ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  line6_dump_finished (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line6_dump_started (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int line6_send_sysex_message (int /*<<< orphan*/ *,char*,int) ; 
 char* pod_alloc_sysex_buffer (struct usb_line6_pod*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pod_resolve (char const*,short,short,char*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_line6_pod* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t pod_send_retrieve_command(struct device *dev, const char *buf, size_t count, short block0, short block1)
{
	struct usb_interface *interface = to_usb_interface(dev);
	struct usb_line6_pod *pod = usb_get_intfdata(interface);
	int size = 4;
	char *sysex = pod_alloc_sysex_buffer(pod, POD_SYSEX_DUMPMEM, size);

	if (!sysex)
		return 0;

	pod_resolve(buf, block0, block1, sysex + SYSEX_DATA_OFS);
	sysex[SYSEX_DATA_OFS + 2] = 0;
	sysex[SYSEX_DATA_OFS + 3] = 0;
	line6_dump_started(&pod->dumpreq, POD_DUMP_MEMORY);

	if (line6_send_sysex_message(&pod->line6, sysex, size) < size)
		line6_dump_finished(&pod->dumpreq);

	kfree(sysex);
	/* needs some delay here on AMD64 platform */
	return count;
}