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
typedef  int /*<<< orphan*/  u16 ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oxygen_write_ac97_masked (struct oxygen*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void oxygen_ac97_set_bits(struct oxygen *chip, unsigned int codec,
					unsigned int index, u16 value)
{
	oxygen_write_ac97_masked(chip, codec, index, value, value);
}