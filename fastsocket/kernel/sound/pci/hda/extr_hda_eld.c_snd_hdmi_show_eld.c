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
struct parsed_hdmi_eld {size_t conn_type; int sad_count; scalar_t__ sad; scalar_t__ spk_alloc; int /*<<< orphan*/  monitor_name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int SND_PRINT_CHANNEL_ALLOCATION_ADVISED_BUFSIZE ; 
 int /*<<< orphan*/  SND_PR_VERBOSE ; 
 int /*<<< orphan*/  _snd_printd (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/ * eld_connection_type_names ; 
 int /*<<< orphan*/  hdmi_show_short_audio_desc (scalar_t__) ; 
 int /*<<< orphan*/  snd_print_channel_allocation (scalar_t__,char*,int) ; 

void snd_hdmi_show_eld(struct parsed_hdmi_eld *e)
{
	int i;

	_snd_printd(SND_PR_VERBOSE, "HDMI: detected monitor %s at connection type %s\n",
			e->monitor_name,
			eld_connection_type_names[e->conn_type]);

	if (e->spk_alloc) {
		char buf[SND_PRINT_CHANNEL_ALLOCATION_ADVISED_BUFSIZE];
		snd_print_channel_allocation(e->spk_alloc, buf, sizeof(buf));
		_snd_printd(SND_PR_VERBOSE, "HDMI: available speakers:%s\n", buf);
	}

	for (i = 0; i < e->sad_count; i++)
		hdmi_show_short_audio_desc(e->sad + i);
}