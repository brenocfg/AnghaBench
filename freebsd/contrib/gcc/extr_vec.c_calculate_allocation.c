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
struct vec_prefix {unsigned int alloc; unsigned int num; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline unsigned
calculate_allocation (const struct vec_prefix *pfx, int reserve, bool exact)
{
  unsigned alloc = 0;
  unsigned num = 0;

  gcc_assert (reserve >= 0);

  if (pfx)
    {
      alloc = pfx->alloc;
      num = pfx->num;
    }
  else if (!reserve)
    /* If there's no prefix, and we've not requested anything, then we
       will create a NULL vector.  */
    return 0;
  
  /* We must have run out of room.  */
  gcc_assert (alloc - num < (unsigned) reserve);
  
  if (exact)
    /* Exact size.  */
    alloc = num + reserve;
  else
    {
      /* Exponential growth. */
      if (!alloc)
	alloc = 4;
      else if (alloc < 16)
	/* Double when small.  */
	alloc = alloc * 2;
      else
	/* Grow slower when large.  */
	alloc = (alloc * 3 / 2);
      
      /* If this is still too small, set it to the right size. */
      if (alloc < num + reserve)
	alloc = num + reserve;
    }
  return alloc;
}