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
typedef  int /*<<< orphan*/  gcov_unsigned_t ;
struct TYPE_2__ {scalar_t__ mode; int offset; unsigned int alloc; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int GCOV_BLOCK_SIZE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcov_allocate (unsigned int) ; 
 TYPE_1__ gcov_var ; 
 int /*<<< orphan*/  gcov_write_block (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static gcov_unsigned_t *
gcov_write_words (unsigned words)
{
  gcov_unsigned_t *result;

  gcc_assert (gcov_var.mode < 0);
#if IN_LIBGCOV
  if (gcov_var.offset >= GCOV_BLOCK_SIZE)
    {
      gcov_write_block (GCOV_BLOCK_SIZE);
      if (gcov_var.offset)
	{
	  gcc_assert (gcov_var.offset == 1);
	  memcpy (gcov_var.buffer, gcov_var.buffer + GCOV_BLOCK_SIZE, 4);
	}
    }
#else
  if (gcov_var.offset + words > gcov_var.alloc)
    gcov_allocate (gcov_var.offset + words);
#endif
  result = &gcov_var.buffer[gcov_var.offset];
  gcov_var.offset += words;
  
  return result;
}