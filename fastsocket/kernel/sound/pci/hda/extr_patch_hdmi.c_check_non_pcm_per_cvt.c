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
struct hda_spdif_out {int status; } ;
struct hda_codec {int /*<<< orphan*/  spdif_mutex; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int IEC958_AES0_NONAUDIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hda_spdif_out* snd_hda_spdif_out_of_nid (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_non_pcm_per_cvt(struct hda_codec *codec, hda_nid_t cvt_nid)
{
	struct hda_spdif_out *spdif;
	bool non_pcm;

	mutex_lock(&codec->spdif_mutex);
	spdif = snd_hda_spdif_out_of_nid(codec, cvt_nid);
	non_pcm = !!(spdif->status & IEC958_AES0_NONAUDIO);
	mutex_unlock(&codec->spdif_mutex);
	return non_pcm;
}