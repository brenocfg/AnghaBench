#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t my_dev; struct TYPE_6__* converter; int /*<<< orphan*/  irq; int /*<<< orphan*/  share_irq; struct TYPE_6__* devc; } ;
typedef  TYPE_1__ uart401_devc ;
struct address_info {int* slots; int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__** midi_devs ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_uart401 (TYPE_1__*) ; 
 int /*<<< orphan*/  sound_unload_mididev (size_t) ; 

void unload_uart401(struct address_info *hw_config)
{
	uart401_devc *devc;
	int n=hw_config->slots[4];
	
	/* Not set up */
	if(n==-1 || midi_devs[n]==NULL)
		return;
		
	/* Not allocated (erm ??) */
	
	devc = midi_devs[hw_config->slots[4]]->devc;
	if (devc == NULL)
		return;

	reset_uart401(devc);
	release_region(hw_config->io_base, 4);

	if (!devc->share_irq)
		free_irq(devc->irq, devc);
	if (devc)
	{
		kfree(midi_devs[devc->my_dev]->converter);
		kfree(midi_devs[devc->my_dev]);
		kfree(devc);
		devc = NULL;
	}
	/* This kills midi_devs[x] */
	sound_unload_mididev(hw_config->slots[4]);
}