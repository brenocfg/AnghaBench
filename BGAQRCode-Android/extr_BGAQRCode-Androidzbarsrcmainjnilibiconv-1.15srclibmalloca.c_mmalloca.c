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
 void* malloc (size_t) ; 

void *
mmalloca (size_t n)
{
#if HAVE_ALLOCA
  /* Allocate one more word, that serves as an indicator for malloc()ed
     memory, so that freea() of an alloca() result is fast.  */
  size_t nplus = n + HEADER_SIZE;

  if (nplus >= n)
    {
      void *p = malloc (nplus);

      if (p != NULL)
        {
          size_t slot;
          union header *h = p;

          p = h + 1;

          /* Put a magic number into the indicator word.  */
          h->magic.word = MAGIC_NUMBER;

          /* Enter p into the hash table.  */
          slot = (uintptr_t) p % HASH_TABLE_SIZE;
          h->next = mmalloca_results[slot];
          mmalloca_results[slot] = p;

          return p;
        }
    }
  /* Out of memory.  */
  return NULL;
#else
# if !MALLOC_0_IS_NONNULL
  if (n == 0)
    n = 1;
# endif
  return malloc (n);
#endif
}