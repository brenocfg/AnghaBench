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
struct snd_cs4231 {unsigned char* image; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  snd_cs4231_dout (struct snd_cs4231*,unsigned char,unsigned char) ; 

__attribute__((used)) static void snd_cs4231_out(struct snd_cs4231 *chip, unsigned char reg,
			   unsigned char value)
{
	snd_cs4231_dout(chip, reg, value);
	chip->image[reg] = value;
	mb();
}