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
struct hda_pcm {char* name; int /*<<< orphan*/ * stream; } ;
struct hda_codec {int num_pcms; struct ad198x_spec* spec; } ;
struct ad198x_spec {struct hda_pcm* pcm_rec; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  ad1984_pcm_dmic_capture ; 
 int ad198x_build_pcms (struct hda_codec*) ; 

__attribute__((used)) static int ad1984_build_pcms(struct hda_codec *codec)
{
	struct ad198x_spec *spec = codec->spec;
	struct hda_pcm *info;
	int err;

	err = ad198x_build_pcms(codec);
	if (err < 0)
		return err;

	info = spec->pcm_rec + codec->num_pcms;
	codec->num_pcms++;
	info->name = "AD1984 Digital Mic";
	info->stream[SNDRV_PCM_STREAM_CAPTURE] = ad1984_pcm_dmic_capture;
	return 0;
}