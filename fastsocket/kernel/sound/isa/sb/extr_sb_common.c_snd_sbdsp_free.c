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
struct snd_sb {scalar_t__ irq; scalar_t__ dma8; scalar_t__ dma16; scalar_t__ res_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  kfree (struct snd_sb*) ; 
 int /*<<< orphan*/  release_and_free_resource (scalar_t__) ; 

__attribute__((used)) static int snd_sbdsp_free(struct snd_sb *chip)
{
	if (chip->res_port)
		release_and_free_resource(chip->res_port);
	if (chip->irq >= 0)
		free_irq(chip->irq, (void *) chip);
#ifdef CONFIG_ISA
	if (chip->dma8 >= 0) {
		disable_dma(chip->dma8);
		free_dma(chip->dma8);
	}
	if (chip->dma16 >= 0 && chip->dma16 != chip->dma8) {
		disable_dma(chip->dma16);
		free_dma(chip->dma16);
	}
#endif
	kfree(chip);
	return 0;
}