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
typedef  int u32 ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_AMPCAP_NUM_STEPS ; 
 int AC_AMPCAP_NUM_STEPS_SHIFT ; 
 int AC_AMPCAP_STEP_SIZE ; 
 int AC_AMPCAP_STEP_SIZE_SHIFT ; 
 unsigned int SNDRV_CTL_TLVT_DB_SCALE ; 
 int query_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

void snd_hda_set_vmaster_tlv(struct hda_codec *codec, hda_nid_t nid, int dir,
			     unsigned int *tlv)
{
	u32 caps;
	int nums, step;

	caps = query_amp_caps(codec, nid, dir);
	nums = (caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT;
	step = (caps & AC_AMPCAP_STEP_SIZE) >> AC_AMPCAP_STEP_SIZE_SHIFT;
	step = (step + 1) * 25;
	tlv[0] = SNDRV_CTL_TLVT_DB_SCALE;
	tlv[1] = 2 * sizeof(unsigned int);
	tlv[2] = -nums * step;
	tlv[3] = step;
}