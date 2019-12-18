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
struct snd_rawmidi_file {struct snd_rawmidi* rmidi; } ;
struct snd_rawmidi {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawmidi_release_priv (struct snd_rawmidi_file*) ; 
 scalar_t__ snd_BUG_ON (int) ; 

int snd_rawmidi_kernel_release(struct snd_rawmidi_file *rfile)
{
	struct snd_rawmidi *rmidi;

	if (snd_BUG_ON(!rfile))
		return -ENXIO;
	
	rmidi = rfile->rmidi;
	rawmidi_release_priv(rfile);
	module_put(rmidi->card->module);
	return 0;
}