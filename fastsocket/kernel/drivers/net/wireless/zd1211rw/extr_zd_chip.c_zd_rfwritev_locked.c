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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int zd_rfwrite_locked (struct zd_chip*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

int zd_rfwritev_locked(struct zd_chip *chip,
	               const u32* values, unsigned int count, u8 bits)
{
	int r;
	unsigned int i;

	for (i = 0; i < count; i++) {
		r = zd_rfwrite_locked(chip, values[i], bits);
		if (r)
			return r;
	}

	return 0;
}