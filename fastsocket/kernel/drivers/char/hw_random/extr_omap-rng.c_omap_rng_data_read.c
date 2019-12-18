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
typedef  int /*<<< orphan*/  u32 ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNG_OUT_REG ; 
 int /*<<< orphan*/  omap_rng_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_rng_data_read(struct hwrng *rng, u32 *data)
{
	*data = omap_rng_read_reg(RNG_OUT_REG);

	return 4;
}