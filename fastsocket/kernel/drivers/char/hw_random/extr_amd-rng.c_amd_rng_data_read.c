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
 scalar_t__ inl (scalar_t__) ; 

__attribute__((used)) static int amd_rng_data_read(struct hwrng *rng, u32 *data)
{
	u32 pmbase = (u32)rng->priv;

	*data = inl(pmbase + 0xF0);

	return 4;
}