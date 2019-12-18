#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_info_buffer {int dummy; } ;
struct hda_pcm {size_t pcm_type; TYPE_2__* pcm; int /*<<< orphan*/  name; TYPE_1__* stream; } ;
struct hda_codec {int num_pcms; struct hda_pcm* pcm_info; } ;
typedef  scalar_t__ hda_nid_t ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {scalar_t__ nid; } ;

/* Variables and functions */
 int /*<<< orphan*/ * snd_hda_pcm_type_name ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_nid_pcms(struct snd_info_buffer *buffer,
			   struct hda_codec *codec, hda_nid_t nid)
{
	int pcm, type;
	struct hda_pcm *cpcm;
	for (pcm = 0; pcm < codec->num_pcms; pcm++) {
		cpcm = &codec->pcm_info[pcm];
		for (type = 0; type < 2; type++) {
			if (cpcm->stream[type].nid != nid || cpcm->pcm == NULL)
				continue;
			snd_iprintf(buffer, "  Device: name=\"%s\", "
				    "type=\"%s\", device=%i\n",
				    cpcm->name,
				    snd_hda_pcm_type_name[cpcm->pcm_type],
				    cpcm->pcm->device);
		}
	}
}