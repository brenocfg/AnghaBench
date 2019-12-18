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
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 scalar_t__ REG_POS (int) ; 
 int /*<<< orphan*/  VEC_POS (int) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int apic_test_and_set_vector(int vec, void *bitmap)
{
	return test_and_set_bit(VEC_POS(vec), (bitmap) + REG_POS(vec));
}