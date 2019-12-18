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
 int /*<<< orphan*/  pgd_offset_k (unsigned long) ; 
 unsigned long uvirt_to_kva (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline unsigned long kvirt_to_kva(unsigned long adr)
{
	unsigned long va, kva;

	va = adr;
	kva = uvirt_to_kva(pgd_offset_k(va), va);

	return kva;
}