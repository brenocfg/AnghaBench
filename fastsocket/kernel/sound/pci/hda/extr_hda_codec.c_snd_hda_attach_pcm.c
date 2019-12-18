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
struct hda_pcm_stream {scalar_t__ substreams; } ;
struct hda_pcm {struct hda_pcm_stream* stream; int /*<<< orphan*/  name; } ;
struct hda_codec {struct hda_bus* bus; } ;
struct TYPE_2__ {int (* attach_pcm ) (struct hda_bus*,struct hda_codec*,struct hda_pcm*) ;} ;
struct hda_bus {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int set_pcm_default_values (struct hda_codec*,struct hda_pcm_stream*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int stub1 (struct hda_bus*,struct hda_codec*,struct hda_pcm*) ; 

__attribute__((used)) static int snd_hda_attach_pcm(struct hda_codec *codec, struct hda_pcm *pcm)
{
	struct hda_bus *bus = codec->bus;
	struct hda_pcm_stream *info;
	int stream, err;

	if (snd_BUG_ON(!pcm->name))
		return -EINVAL;
	for (stream = 0; stream < 2; stream++) {
		info = &pcm->stream[stream];
		if (info->substreams) {
			err = set_pcm_default_values(codec, info);
			if (err < 0)
				return err;
		}
	}
	return bus->ops.attach_pcm(bus, codec, pcm);
}