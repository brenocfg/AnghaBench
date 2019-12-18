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
struct snd_pmac {int /*<<< orphan*/  (* update_automute ) (struct snd_pmac*,int) ;scalar_t__ initialized; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  stub1 (struct snd_pmac*,int) ; 

__attribute__((used)) static irqreturn_t headphone_intr(int irq, void *devid)
{
	struct snd_pmac *chip = devid;
	if (chip->update_automute && chip->initialized) {
		chip->update_automute(chip, 1);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}