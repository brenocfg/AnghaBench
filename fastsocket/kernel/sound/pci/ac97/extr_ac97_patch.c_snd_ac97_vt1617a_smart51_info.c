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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int ac97_enum_text_info (struct snd_kcontrol*,struct snd_ctl_elem_info*,char const**,int) ; 

__attribute__((used)) static int snd_ac97_vt1617a_smart51_info(struct snd_kcontrol *kcontrol,
					 struct snd_ctl_elem_info *uinfo)
{
	/* ordering in this list reflects vt1617a docs for Reg 20 and
	 * 7a and Table 6 that lays out the matrix NB WRT Table6: SM51
	 * is SM51EN *AND* it's Bit14, not Bit15 so the table is very
	 * counter-intuitive */ 

	static const char* texts[] = { "LineIn Mic1", "LineIn Mic1 Mic3",
				       "Surr LFE/C Mic3", "LineIn LFE/C Mic3",
				       "LineIn Mic2", "LineIn Mic2 Mic1",
				       "Surr LFE Mic1", "Surr LFE Mic1 Mic2"};
	return ac97_enum_text_info(kcontrol, uinfo, texts, 8);
}