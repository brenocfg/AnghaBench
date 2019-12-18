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

/* Variables and functions */
 int /*<<< orphan*/  dsfmt_genrand_uint32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsfmt_global_data ; 

__attribute__((used)) inline static uint32_t dsfmt_gv_genrand_uint32(void) {
    return dsfmt_genrand_uint32(&dsfmt_global_data);
}