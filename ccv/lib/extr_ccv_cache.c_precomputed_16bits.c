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

/* Variables and functions */
 int /*<<< orphan*/ * bits_in_16bits ; 
 int bits_in_16bits_init ; 
 int /*<<< orphan*/  sparse_bitcount (int) ; 

__attribute__((used)) static void precomputed_16bits() {
	int i;
	for (i = 0; i < (0x1u << 16); i++)
		bits_in_16bits[i] = sparse_bitcount(i);
	bits_in_16bits_init = 1;
}