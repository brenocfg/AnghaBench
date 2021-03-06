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
struct snd_seq_device {int /*<<< orphan*/  card; struct snd_emu8000* driver_data; } ;
struct snd_emu8000 {int /*<<< orphan*/ * memhdr; int /*<<< orphan*/ * emu; scalar_t__ pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_emux_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_util_memhdr_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_emu8000_delete_device(struct snd_seq_device *dev)
{
	struct snd_emu8000 *hw;

	if (dev->driver_data == NULL)
		return 0; /* no synth was allocated actually */

	hw = dev->driver_data;
	if (hw->pcm)
		snd_device_free(dev->card, hw->pcm);
	if (hw->emu)
		snd_emux_free(hw->emu);
	if (hw->memhdr)
		snd_util_memhdr_free(hw->memhdr);
	hw->emu = NULL;
	hw->memhdr = NULL;
	return 0;
}