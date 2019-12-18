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
 int RME9652_IE ; 
 int /*<<< orphan*/  RME9652_control_register ; 
 int RME9652_start_bit ; 
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void rme9652_start(struct snd_rme9652 *s)
{
	s->control_register |= (RME9652_IE | RME9652_start_bit);
	rme9652_write(s, RME9652_control_register, s->control_register);
}