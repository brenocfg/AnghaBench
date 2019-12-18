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
typedef  int /*<<< orphan*/  hashval_t ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  iterative_hash_hashval_t (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline hashval_t
iterative_hash_host_wide_int (HOST_WIDE_INT val, hashval_t val2)
{
  if (sizeof (HOST_WIDE_INT) == sizeof (hashval_t))
    return iterative_hash_hashval_t (val, val2);
  else
    {
      hashval_t a = (hashval_t) val;
      /* Avoid warnings about shifting of more than the width of the type on
         hosts that won't execute this path.  */
      int zero = 0;
      hashval_t b = (hashval_t) (val >> (sizeof (hashval_t) * 8 + zero));
      mix (a, b, val2);
      if (sizeof (HOST_WIDE_INT) > 2 * sizeof (hashval_t))
	{
	  hashval_t a = (hashval_t) (val >> (sizeof (hashval_t) * 16 + zero));
	  hashval_t b = (hashval_t) (val >> (sizeof (hashval_t) * 24 + zero));
	  mix (a, b, val2);
	}
      return val2;
    }
}