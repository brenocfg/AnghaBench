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
struct mem_chunk {int type; unsigned long addr; unsigned long size; } ;

/* Variables and functions */

__attribute__((used)) static void mem_chunk_init(struct mem_chunk *chunk, unsigned long addr,
			   unsigned long size, int type)
{
	chunk->type = type;
	chunk->addr = addr;
	chunk->size = size;
}