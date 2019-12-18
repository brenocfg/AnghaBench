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
struct TYPE_2__ {int tune; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_TYPE_B ; 
 int /*<<< orphan*/  IA64_TYPE_F ; 
 int /*<<< orphan*/  IA64_TYPE_I ; 
 int /*<<< orphan*/  IA64_TYPE_M ; 
 int /*<<< orphan*/  abort () ; 
#define  itanium1 129 
#define  itanium2 128 
 int /*<<< orphan*/  match (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ md ; 

__attribute__((used)) static inline int
extra_goodness (int templ, int slot)
{
  switch (md.tune)
    {
    case itanium1:
      if (slot == 1 && match (templ, IA64_TYPE_F, slot))
	return 2;
      else if (slot == 2 && match (templ, IA64_TYPE_B, slot))
	return 1;
      else
	return 0;
      break;
    case itanium2:
      if (match (templ, IA64_TYPE_M, slot)
	  || match (templ, IA64_TYPE_I, slot))
	/* Favor M- and I-unit NOPs.  We definitely want to avoid
	   F-unit and B-unit may cause split-issue or less-than-optimal
	   branch-prediction.  */
	return 2;
      else
	return 0;
      break;
    default:
      abort ();
      return 0;
    }
}