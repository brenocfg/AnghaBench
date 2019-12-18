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
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 scalar_t__ A_MICROCODEBASE ; 
 scalar_t__ MICROCODEBASE ; 
 unsigned int snd_emu10k1_ptr_read (struct snd_emu10k1*,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int snd_emu10k1_efx_read(struct snd_emu10k1 *emu, unsigned int pc)
{
	pc += emu->audigy ? A_MICROCODEBASE : MICROCODEBASE;
	return snd_emu10k1_ptr_read(emu, pc, 0);
}