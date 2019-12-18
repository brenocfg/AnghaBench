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
struct snd_ca_midi {int /*<<< orphan*/ * rmidi; int /*<<< orphan*/ * get_dev_id_port; int /*<<< orphan*/ * get_dev_id_card; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; int /*<<< orphan*/ * interrupt_disable; int /*<<< orphan*/ * interrupt_enable; int /*<<< orphan*/ * interrupt; } ;

/* Variables and functions */

__attribute__((used)) static void ca_midi_free(struct snd_ca_midi *midi)
{
	midi->interrupt = NULL;
	midi->interrupt_enable = NULL;
	midi->interrupt_disable = NULL;
	midi->read = NULL;
	midi->write = NULL;
	midi->get_dev_id_card = NULL;
	midi->get_dev_id_port = NULL;
	midi->rmidi = NULL;
}