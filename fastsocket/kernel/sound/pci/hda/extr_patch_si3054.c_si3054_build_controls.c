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
 int /*<<< orphan*/  si3054_modem_mixer ; 
 int snd_hda_add_new_ctls (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si3054_build_controls(struct hda_codec *codec)
{
	return snd_hda_add_new_ctls(codec, si3054_modem_mixer);
}