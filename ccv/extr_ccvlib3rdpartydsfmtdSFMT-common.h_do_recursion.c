#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {int* u; } ;
typedef  TYPE_1__ dw128_t ;

/* Variables and functions */
 int DSFMT_MSK1 ; 
 int DSFMT_MSK2 ; 
 int DSFMT_SL1 ; 
 int DSFMT_SR ; 

__attribute__((used)) inline static void do_recursion(dw128_t *r, dw128_t *a, dw128_t * b,
				dw128_t *lung) {
    uint64_t t0, t1, L0, L1;

    t0 = a->u[0];
    t1 = a->u[1];
    L0 = lung->u[0];
    L1 = lung->u[1];
    lung->u[0] = (t0 << DSFMT_SL1) ^ (L1 >> 32) ^ (L1 << 32) ^ b->u[0];
    lung->u[1] = (t1 << DSFMT_SL1) ^ (L0 >> 32) ^ (L0 << 32) ^ b->u[1];
    r->u[0] = (lung->u[0] >> DSFMT_SR) ^ (lung->u[0] & DSFMT_MSK1) ^ t0;
    r->u[1] = (lung->u[1] >> DSFMT_SR) ^ (lung->u[1] & DSFMT_MSK2) ^ t1;
}