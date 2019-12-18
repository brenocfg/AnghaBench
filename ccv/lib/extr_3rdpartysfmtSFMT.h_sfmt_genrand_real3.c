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
typedef  int /*<<< orphan*/  sfmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  sfmt_genrand_uint32 (int /*<<< orphan*/ *) ; 
 double sfmt_to_real3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static double sfmt_genrand_real3(sfmt_t * sfmt)
{
    return sfmt_to_real3(sfmt_genrand_uint32(sfmt));
}