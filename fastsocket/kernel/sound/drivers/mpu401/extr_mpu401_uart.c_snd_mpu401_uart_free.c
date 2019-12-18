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
struct snd_rawmidi {struct snd_mpu401* private_data; } ;
struct snd_mpu401 {scalar_t__ irq; int /*<<< orphan*/  res; scalar_t__ irq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  kfree (struct snd_mpu401*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_mpu401_uart_free(struct snd_rawmidi *rmidi)
{
	struct snd_mpu401 *mpu = rmidi->private_data;
	if (mpu->irq_flags && mpu->irq >= 0)
		free_irq(mpu->irq, (void *) mpu);
	release_and_free_resource(mpu->res);
	kfree(mpu);
}