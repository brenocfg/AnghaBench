#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint32_t ;
struct TYPE_4__ {int* A; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  const READU16 (TYPE_1__*,int) ; 

__attribute__((used)) static inline uint32_t POP16(Q68State *state) {
    const uint32_t data = READU16(state, state->A[7]);
    state->A[7] += 2;
    return data;
}