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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE16 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void WRITE32(Q68State *state, uint32_t addr, uint32_t data) {
    WRITE16(state, addr, data>>16);
    WRITE16(state, addr+2, data);
}