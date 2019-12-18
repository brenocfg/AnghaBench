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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_XOR_BLOCKS ; 
 int /*<<< orphan*/  XOR_SIZE ; 
 int /*<<< orphan*/  xor_blocks (unsigned int,int /*<<< orphan*/ ,void*,void**) ; 

__attribute__((used)) static void xor_blocks_wrapper(unsigned n, unsigned long **data)
{
	BUG_ON(n < 2 || n > MAX_XOR_BLOCKS + 1);
	xor_blocks(n - 1, XOR_SIZE, (void *) data[0], (void **) data + 1);
}