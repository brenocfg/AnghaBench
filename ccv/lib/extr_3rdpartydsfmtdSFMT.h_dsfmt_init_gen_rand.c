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
typedef  int /*<<< orphan*/  dsfmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSFMT_MEXP ; 
 int /*<<< orphan*/  dsfmt_chk_init_gen_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void dsfmt_init_gen_rand(dsfmt_t *dsfmt, uint32_t seed) {
    dsfmt_chk_init_gen_rand(dsfmt, seed, DSFMT_MEXP);
}