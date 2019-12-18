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
#define  CONEXANT_HP_EVENT 129 
#define  CONEXANT_MIC_EVENT 128 
 int /*<<< orphan*/  cxt5045_hp_automic (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5045_hp_automute (struct hda_codec*) ; 

__attribute__((used)) static void cxt5045_hp_unsol_event(struct hda_codec *codec,
				   unsigned int res)
{
	res >>= 26;
	switch (res) {
	case CONEXANT_HP_EVENT:
		cxt5045_hp_automute(codec);
		break;
	case CONEXANT_MIC_EVENT:
		cxt5045_hp_automic(codec);
		break;

	}
}