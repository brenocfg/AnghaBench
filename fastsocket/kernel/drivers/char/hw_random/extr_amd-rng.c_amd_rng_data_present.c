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
typedef  scalar_t__ u32 ;
struct hwrng {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int amd_rng_data_present(struct hwrng *rng, int wait)
{
	u32 pmbase = (u32)rng->priv;
	int data, i;

	for (i = 0; i < 20; i++) {
		data = !!(inl(pmbase + 0xF4) & 1);
		if (data || !wait)
			break;
		udelay(10);
	}
	return data;
}