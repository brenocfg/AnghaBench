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
struct talitos_ptr {void* eptr; void* ptr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void to_talitos_ptr(struct talitos_ptr *talitos_ptr, dma_addr_t dma_addr)
{
	talitos_ptr->ptr = cpu_to_be32(lower_32_bits(dma_addr));
	talitos_ptr->eptr = cpu_to_be32(upper_32_bits(dma_addr));
}