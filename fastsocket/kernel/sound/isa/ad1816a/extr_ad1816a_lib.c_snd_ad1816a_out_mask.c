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
struct snd_ad1816a {int dummy; } ;

/* Variables and functions */
 unsigned char snd_ad1816a_in (struct snd_ad1816a*,unsigned char) ; 
 int /*<<< orphan*/  snd_ad1816a_out (struct snd_ad1816a*,unsigned char,unsigned char) ; 

__attribute__((used)) static inline void snd_ad1816a_out_mask(struct snd_ad1816a *chip, unsigned char reg,
				 unsigned char mask, unsigned char value)
{
	snd_ad1816a_out(chip, reg,
		(value & mask) | (snd_ad1816a_in(chip, reg) & ~mask));
}