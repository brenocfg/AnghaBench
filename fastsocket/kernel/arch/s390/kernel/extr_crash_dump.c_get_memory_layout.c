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
struct mem_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_CRASHK ; 
 int MEMORY_CHUNKS ; 
 int /*<<< orphan*/  OLDMEM_BASE ; 
 int /*<<< orphan*/  OLDMEM_SIZE ; 
 int /*<<< orphan*/  create_mem_hole (struct mem_chunk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detect_memory_layout (struct mem_chunk*) ; 
 struct mem_chunk* kzalloc_panic (int) ; 

__attribute__((used)) static struct mem_chunk *get_memory_layout(void)
{
	struct mem_chunk *chunk_array;

	chunk_array = kzalloc_panic(MEMORY_CHUNKS * sizeof(struct mem_chunk));
	detect_memory_layout(chunk_array);
	create_mem_hole(chunk_array, OLDMEM_BASE, OLDMEM_SIZE, CHUNK_CRASHK);
	return chunk_array;
}