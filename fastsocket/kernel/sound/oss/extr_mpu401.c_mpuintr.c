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
struct mpu_config {scalar_t__ base; int opened; scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 scalar_t__ MODE_SYNTH ; 
 int OPEN_READ ; 
 struct mpu_config* dev_conf ; 
 scalar_t__ input_avail (struct mpu_config*) ; 
 int /*<<< orphan*/  mpu401_input_loop (struct mpu_config*) ; 
 int /*<<< orphan*/  read_data (struct mpu_config*) ; 

__attribute__((used)) static irqreturn_t mpuintr(int irq, void *dev_id)
{
	struct mpu_config *devc;
	int dev = (int)(unsigned long) dev_id;
	int handled = 0;

	devc = &dev_conf[dev];

	if (input_avail(devc))
	{
		handled = 1;
		if (devc->base != 0 && (devc->opened & OPEN_READ || devc->mode == MODE_SYNTH))
			mpu401_input_loop(devc);
		else
		{
			/* Dummy read (just to acknowledge the interrupt) */
			read_data(devc);
		}
	}
	return IRQ_RETVAL(handled);
}