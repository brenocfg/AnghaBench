#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fx_status; } ;
typedef  TYPE_1__ snd_wavefront_t ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printk (char*) ; 

int
snd_wavefront_fx_detect (snd_wavefront_t *dev)

{
	/* This is a crude check, but its the best one I have for now.
	   Certainly on the Maui and the Tropez, wavefront_fx_idle() will
	   report "never idle", which suggests that this test should
	   work OK.
	*/

	if (inb (dev->fx_status) & 0x80) {
		snd_printk ("Hmm, probably a Maui or Tropez.\n");
		return -1;
	}

	return 0;
}