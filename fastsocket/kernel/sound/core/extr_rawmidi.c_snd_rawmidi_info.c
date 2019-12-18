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
struct snd_rawmidi_substream {TYPE_2__* pstr; int /*<<< orphan*/  name; int /*<<< orphan*/  stream; int /*<<< orphan*/  number; struct snd_rawmidi* rmidi; } ;
struct snd_rawmidi_info {scalar_t__ subdevices_avail; scalar_t__ subdevices_count; int /*<<< orphan*/  subname; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; int /*<<< orphan*/  stream; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  device; int /*<<< orphan*/  card; } ;
struct snd_rawmidi {int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  info_flags; int /*<<< orphan*/  device; TYPE_1__* card; } ;
struct TYPE_4__ {scalar_t__ substream_opened; scalar_t__ substream_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  memset (struct snd_rawmidi_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_rawmidi_info(struct snd_rawmidi_substream *substream,
			    struct snd_rawmidi_info *info)
{
	struct snd_rawmidi *rmidi;
	
	if (substream == NULL)
		return -ENODEV;
	rmidi = substream->rmidi;
	memset(info, 0, sizeof(*info));
	info->card = rmidi->card->number;
	info->device = rmidi->device;
	info->subdevice = substream->number;
	info->stream = substream->stream;
	info->flags = rmidi->info_flags;
	strcpy(info->id, rmidi->id);
	strcpy(info->name, rmidi->name);
	strcpy(info->subname, substream->name);
	info->subdevices_count = substream->pstr->substream_count;
	info->subdevices_avail = (substream->pstr->substream_count -
				  substream->pstr->substream_opened);
	return 0;
}