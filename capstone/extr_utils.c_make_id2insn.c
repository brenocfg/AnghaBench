#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short id; } ;
typedef  TYPE_1__ insn_map ;

/* Variables and functions */
 scalar_t__ cs_mem_calloc (unsigned short,int) ; 

__attribute__((used)) static unsigned short *make_id2insn(const insn_map *insns, unsigned int size)
{
	// NOTE: assume that the max id is always put at the end of insns array
	unsigned short max_id = insns[size - 1].id;
	unsigned short i;

	unsigned short *cache = (unsigned short *)cs_mem_calloc(max_id + 1, sizeof(*cache));

	for (i = 1; i < size; i++)
		cache[insns[i].id] = i;

	return cache;
}