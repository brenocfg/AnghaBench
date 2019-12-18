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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sfmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  sfmt_genrand_uint32 (int /*<<< orphan*/ *) ; 
 double sfmt_to_res53_mix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static double sfmt_genrand_res53_mix(sfmt_t * sfmt)
{
    uint32_t x, y;

    x = sfmt_genrand_uint32(sfmt);
    y = sfmt_genrand_uint32(sfmt);
    return sfmt_to_res53_mix(x, y);
}