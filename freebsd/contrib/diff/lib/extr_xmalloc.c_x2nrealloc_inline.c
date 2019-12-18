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
 int SIZE_MAX ; 
 int /*<<< orphan*/  xalloc_die () ; 
 void* xrealloc (void*,size_t) ; 

__attribute__((used)) static inline void *
x2nrealloc_inline (void *p, size_t *pn, size_t s)
{
  size_t n = *pn;

  if (! p)
    {
      if (! n)
	{
	  /* The approximate size to use for initial small allocation
	     requests, when the invoking code specifies an old size of
	     zero.  64 bytes is the largest "small" request for the
	     GNU C library malloc.  */
	  enum { DEFAULT_MXFAST = 64 };

	  n = DEFAULT_MXFAST / s;
	  n += !n;
	}
    }
  else
    {
      if (SIZE_MAX / 2 / s < n)
	xalloc_die ();
      n *= 2;
    }

  *pn = n;
  return xrealloc (p, n * s);
}