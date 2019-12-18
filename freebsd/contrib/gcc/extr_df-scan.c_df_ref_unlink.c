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
struct df_ref {struct df_ref* next_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static struct df_ref *
df_ref_unlink (struct df_ref *chain, struct df_ref *ref)
{
  struct df_ref *orig_chain = chain;
  struct df_ref *prev = NULL;
  while (chain)
    {
      if (chain == ref)
	{
	  if (prev)
	    {
	      prev->next_ref = ref->next_ref;
	      ref->next_ref = NULL;
	      return orig_chain;
	    }
	  else
	    {
	      chain = ref->next_ref;
	      ref->next_ref = NULL;
	      return chain;
	    }
	}

      prev = chain;
      chain = chain->next_ref;
    }

  /* Someone passed in a ref that was not in the chain.  */
  gcc_unreachable ();
  return NULL;
}