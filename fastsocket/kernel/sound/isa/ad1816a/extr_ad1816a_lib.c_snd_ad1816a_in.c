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
 int /*<<< orphan*/  AD1816A_REG (unsigned char) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ad1816a_busy_wait (struct snd_ad1816a*) ; 

__attribute__((used)) static inline unsigned char snd_ad1816a_in(struct snd_ad1816a *chip, unsigned char reg)
{
	snd_ad1816a_busy_wait(chip);
	return inb(AD1816A_REG(reg));
}