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
struct snd_gf1_mem_block {unsigned int ptr; struct snd_gf1_mem_block* next; } ;
struct snd_gf1_mem {struct snd_gf1_mem_block* first; } ;

/* Variables and functions */

__attribute__((used)) static struct snd_gf1_mem_block *snd_gf1_mem_look(struct snd_gf1_mem * alloc,
					     unsigned int address)
{
	struct snd_gf1_mem_block *block;

	for (block = alloc->first; block; block = block->next) {
		if (block->ptr == address) {
			return block;
		}
	}
	return NULL;
}