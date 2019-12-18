#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct alloc_zone {size_t high_free_bin; struct alloc_chunk** free_chunks; } ;
struct alloc_chunk {size_t size; struct alloc_chunk* next_free; } ;
struct TYPE_2__ {int /*<<< orphan*/  debug_file; } ;

/* Variables and functions */
 TYPE_1__ G ; 
 int GGC_DEBUG_LEVEL ; 
 size_t NUM_FREE_BINS ; 
 size_t SIZE_BIN_DOWN (size_t) ; 
 int /*<<< orphan*/  VALGRIND_DISCARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_NOACCESS (char*,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_WRITABLE (struct alloc_chunk*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline void
free_chunk (char *ptr, size_t size, struct alloc_zone *zone)
{
  struct alloc_chunk *chunk = (struct alloc_chunk *) ptr;
  size_t bin = 0;

  bin = SIZE_BIN_DOWN (size);
  gcc_assert (bin != 0);
  if (bin > NUM_FREE_BINS)
    {
      bin = 0;
      VALGRIND_DISCARD (VALGRIND_MAKE_WRITABLE (chunk, sizeof (struct alloc_chunk)));
      chunk->size = size;
      chunk->next_free = zone->free_chunks[bin];
      VALGRIND_DISCARD (VALGRIND_MAKE_NOACCESS (ptr + sizeof (struct alloc_chunk),
						size - sizeof (struct alloc_chunk)));
    }
  else
    {
      VALGRIND_DISCARD (VALGRIND_MAKE_WRITABLE (chunk, sizeof (struct alloc_chunk *)));
      chunk->next_free = zone->free_chunks[bin];
      VALGRIND_DISCARD (VALGRIND_MAKE_NOACCESS (ptr + sizeof (struct alloc_chunk *),
						size - sizeof (struct alloc_chunk *)));
    }

  zone->free_chunks[bin] = chunk;
  if (bin > zone->high_free_bin)
    zone->high_free_bin = bin;
  if (GGC_DEBUG_LEVEL >= 3)
    fprintf (G.debug_file, "Deallocating object, chunk=%p\n", (void *)chunk);
}