#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {int /*<<< orphan*/  hash_mutex; } ;
struct TYPE_2__ {int val; } ;
struct hda_amp_info {unsigned int* vol; TYPE_1__ head; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_AMP_GET_INPUT ; 
 unsigned int AC_AMP_GET_LEFT ; 
 unsigned int AC_AMP_GET_OUTPUT ; 
 unsigned int AC_AMP_GET_RIGHT ; 
 int /*<<< orphan*/  AC_VERB_GET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  HDA_HASH_KEY (int /*<<< orphan*/ ,int,int) ; 
 int HDA_OUTPUT ; 
 int INFO_AMP_VOL (int) ; 
 struct hda_amp_info* get_alloc_amp_hash (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct hda_amp_info *
update_amp_hash(struct hda_codec *codec, hda_nid_t nid, int ch,
		int direction, int index, bool init_only)
{
	struct hda_amp_info *info;
	unsigned int parm, val = 0;
	bool val_read = false;

 retry:
	info = get_alloc_amp_hash(codec, HDA_HASH_KEY(nid, direction, index));
	if (!info)
		return NULL;
	if (!(info->head.val & INFO_AMP_VOL(ch))) {
		if (!val_read) {
			mutex_unlock(&codec->hash_mutex);
			parm = ch ? AC_AMP_GET_RIGHT : AC_AMP_GET_LEFT;
			parm |= direction == HDA_OUTPUT ?
				AC_AMP_GET_OUTPUT : AC_AMP_GET_INPUT;
			parm |= index;
			val = snd_hda_codec_read(codec, nid, 0,
				 AC_VERB_GET_AMP_GAIN_MUTE, parm);
			val &= 0xff;
			val_read = true;
			mutex_lock(&codec->hash_mutex);
			goto retry;
		}
		info->vol[ch] = val;
		info->head.val |= INFO_AMP_VOL(ch);
	} else if (init_only)
		return NULL;
	return info;
}