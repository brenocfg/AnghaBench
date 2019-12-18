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
struct pcpu_chunk {int free_size; int contig_hint; } ;

/* Variables and functions */
 int pcpu_size_to_slot (int) ; 

__attribute__((used)) static int pcpu_chunk_slot(const struct pcpu_chunk *chunk)
{
	if (chunk->free_size < sizeof(int) || chunk->contig_hint < sizeof(int))
		return 0;

	return pcpu_size_to_slot(chunk->free_size);
}