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
struct snd_cs46xx {int dummy; } ;
struct TYPE_4__ {TYPE_1__* memory; int /*<<< orphan*/ * map; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 TYPE_2__ BA1Struct ; 
 int BA1_MEMORY_COUNT ; 
 int snd_cs46xx_download (struct snd_cs46xx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int snd_cs46xx_download_image(struct snd_cs46xx *chip)
{
	int idx, err;
	unsigned long offset = 0;

	for (idx = 0; idx < BA1_MEMORY_COUNT; idx++) {
		if ((err = snd_cs46xx_download(chip,
					       &BA1Struct.map[offset],
					       BA1Struct.memory[idx].offset,
					       BA1Struct.memory[idx].size)) < 0)
			return err;
		offset += BA1Struct.memory[idx].size >> 2;
	}	
	return 0;
}