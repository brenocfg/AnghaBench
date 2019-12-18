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
struct snd_ac97_bus {int /*<<< orphan*/  (* private_free ) (struct snd_ac97_bus*) ;struct snd_ac97_bus* pcms; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_ac97_bus*) ; 
 int /*<<< orphan*/  snd_ac97_bus_proc_done (struct snd_ac97_bus*) ; 
 int /*<<< orphan*/  stub1 (struct snd_ac97_bus*) ; 

__attribute__((used)) static int snd_ac97_bus_free(struct snd_ac97_bus *bus)
{
	if (bus) {
		snd_ac97_bus_proc_done(bus);
		kfree(bus->pcms);
		if (bus->private_free)
			bus->private_free(bus);
		kfree(bus);
	}
	return 0;
}