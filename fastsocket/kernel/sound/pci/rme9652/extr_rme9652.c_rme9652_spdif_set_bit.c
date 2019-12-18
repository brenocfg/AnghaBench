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
struct snd_rme9652 {int control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  RME9652_control_register ; 
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rme9652_spdif_set_bit (struct snd_rme9652 *rme9652, int mask, int onoff)
{
	if (onoff) 
		rme9652->control_register |= mask;
	else 
		rme9652->control_register &= ~mask;
		
	rme9652_write(rme9652, RME9652_control_register, rme9652->control_register);
}