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
typedef  int /*<<< orphan*/  u8 ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_clear_dip_buffers (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_debug_dip_size (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_set_dip_index (struct hda_codec*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdmi_write_dip_byte (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_fill_audio_infoframe(struct hda_codec *codec,
				      hda_nid_t pin_nid,
				      u8 *dip, int size)
{
	int i;

	hdmi_debug_dip_size(codec, pin_nid);
	hdmi_clear_dip_buffers(codec, pin_nid); /* be paranoid */

	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	for (i = 0; i < size; i++)
		hdmi_write_dip_byte(codec, pin_nid, dip[i]);
}