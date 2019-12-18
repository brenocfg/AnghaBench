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
struct TYPE_2__ {unsigned int length; unsigned int offset; scalar_t__ mode; unsigned int start; unsigned int alloc; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  overread; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 unsigned int GCOV_BLOCK_SIZE ; 
 int fread (int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcov_allocate (unsigned int) ; 
 TYPE_1__ gcov_var ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static const gcov_unsigned_t *
gcov_read_words (unsigned words)
{
  const gcov_unsigned_t *result;
  unsigned excess = gcov_var.length - gcov_var.offset;
  
  gcc_assert (gcov_var.mode > 0);
  if (excess < words)
    {
      gcov_var.start += gcov_var.offset;
#if IN_LIBGCOV
      if (excess)
	{
	  gcc_assert (excess == 1);
	  memcpy (gcov_var.buffer, gcov_var.buffer + gcov_var.offset, 4);
	}
#else
      memmove (gcov_var.buffer, gcov_var.buffer + gcov_var.offset, excess * 4);
#endif
      gcov_var.offset = 0;
      gcov_var.length = excess;
#if IN_LIBGCOV
      gcc_assert (!gcov_var.length || gcov_var.length == 1);
      excess = GCOV_BLOCK_SIZE;
#else
      if (gcov_var.length + words > gcov_var.alloc)
	gcov_allocate (gcov_var.length + words);
      excess = gcov_var.alloc - gcov_var.length;
#endif
      excess = fread (gcov_var.buffer + gcov_var.length,
		      1, excess << 2, gcov_var.file) >> 2;
      gcov_var.length += excess;
      if (gcov_var.length < words)
	{
	  gcov_var.overread += words - gcov_var.length;
	  gcov_var.length = 0;
	  return 0;
	}
    }
  result = &gcov_var.buffer[gcov_var.offset];
  gcov_var.offset += words;
  return result;
}