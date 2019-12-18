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
#define  AD1884A_HP_EVENT 129 
#define  AD1884A_MIC_EVENT 128 
 int /*<<< orphan*/  ad1884a_hp_automute (struct hda_codec*) ; 
 int /*<<< orphan*/  ad1984a_touchsmart_automic (struct hda_codec*) ; 

__attribute__((used)) static void ad1984a_touchsmart_unsol_event(struct hda_codec *codec,
	unsigned int res)
{
	switch (res >> 26) {
	case AD1884A_HP_EVENT:
		ad1884a_hp_automute(codec);
		break;
	case AD1884A_MIC_EVENT:
		ad1984a_touchsmart_automic(codec);
		break;
	}
}