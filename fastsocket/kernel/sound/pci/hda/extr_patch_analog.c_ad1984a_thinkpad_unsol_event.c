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
 unsigned int AD1884A_HP_EVENT ; 
 int /*<<< orphan*/  ad1984a_thinkpad_automute (struct hda_codec*) ; 

__attribute__((used)) static void ad1984a_thinkpad_unsol_event(struct hda_codec *codec,
					 unsigned int res)
{
	if ((res >> 26) != AD1884A_HP_EVENT)
		return;
	ad1984a_thinkpad_automute(codec);
}