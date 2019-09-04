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
 int /*<<< orphan*/  dsfmt_global_data ; 
 int /*<<< orphan*/  dsfmt_init_gen_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void dsfmt_gv_init_gen_rand(uint32_t seed) {
    dsfmt_init_gen_rand(&dsfmt_global_data, seed);
}