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
struct TYPE_3__ {int /*<<< orphan*/  mem_alloc; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;
struct TYPE_4__ {int /*<<< orphan*/  memory; } ;
struct iwffff_wave {int format; TYPE_2__ address; } ;

/* Variables and functions */
 int IWFFFF_WAVE_ROM ; 
 int snd_gf1_mem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int snd_gus_iwffff_remove_sample(void *private_data, struct iwffff_wave *wave,
				 int atomic)
{
	struct snd_gus_card *gus = private_data;

	if (wave->format & IWFFFF_WAVE_ROM)
		return 0;	/* it's probably ok - verify the address? */	
	return snd_gf1_mem_free(&gus->gf1.mem_alloc, wave->address.memory);
}