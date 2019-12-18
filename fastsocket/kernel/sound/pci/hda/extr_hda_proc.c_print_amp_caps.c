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
struct snd_info_buffer {int dummy; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_AMPCAP_MUTE ; 
 unsigned int AC_AMPCAP_MUTE_SHIFT ; 
 unsigned int AC_AMPCAP_NUM_STEPS ; 
 unsigned int AC_AMPCAP_NUM_STEPS_SHIFT ; 
 unsigned int AC_AMPCAP_OFFSET ; 
 unsigned int AC_AMPCAP_STEP_SIZE ; 
 unsigned int AC_AMPCAP_STEP_SIZE_SHIFT ; 
 int /*<<< orphan*/  AC_PAR_AMP_IN_CAP ; 
 int /*<<< orphan*/  AC_PAR_AMP_OUT_CAP ; 
 int HDA_OUTPUT ; 
 unsigned int snd_hda_param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void print_amp_caps(struct snd_info_buffer *buffer,
			   struct hda_codec *codec, hda_nid_t nid, int dir)
{
	unsigned int caps;
	caps = snd_hda_param_read(codec, nid,
				  dir == HDA_OUTPUT ?
				    AC_PAR_AMP_OUT_CAP : AC_PAR_AMP_IN_CAP);
	if (caps == -1 || caps == 0) {
		snd_iprintf(buffer, "N/A\n");
		return;
	}
	snd_iprintf(buffer, "ofs=0x%02x, nsteps=0x%02x, stepsize=0x%02x, "
		    "mute=%x\n",
		    caps & AC_AMPCAP_OFFSET,
		    (caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT,
		    (caps & AC_AMPCAP_STEP_SIZE) >> AC_AMPCAP_STEP_SIZE_SHIFT,
		    (caps & AC_AMPCAP_MUTE) >> AC_AMPCAP_MUTE_SHIFT);
}