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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_hp_automute (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_line_automute (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_mic_autoswitch (struct hda_codec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_automute_all(struct hda_codec *codec)
{
	call_hp_automute(codec, NULL);
	call_line_automute(codec, NULL);
	call_mic_autoswitch(codec, NULL);
}