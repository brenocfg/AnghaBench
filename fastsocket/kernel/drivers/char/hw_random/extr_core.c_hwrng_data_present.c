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
struct hwrng {int (* data_present ) (struct hwrng*,int) ;} ;

/* Variables and functions */
 int stub1 (struct hwrng*,int) ; 

__attribute__((used)) static inline int hwrng_data_present(struct hwrng *rng, int wait)
{
	if (!rng->data_present)
		return 1;
	return rng->data_present(rng, wait);
}