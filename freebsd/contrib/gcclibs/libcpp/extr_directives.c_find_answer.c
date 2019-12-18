#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct answer {unsigned int count; int /*<<< orphan*/ * first; struct answer* next; } ;
struct TYPE_4__ {struct answer* answers; } ;
struct TYPE_5__ {TYPE_1__ value; } ;
typedef  TYPE_2__ cpp_hashnode ;

/* Variables and functions */
 int /*<<< orphan*/  _cpp_equiv_tokens (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct answer **
find_answer (cpp_hashnode *node, const struct answer *candidate)
{
  unsigned int i;
  struct answer **result;

  for (result = &node->value.answers; *result; result = &(*result)->next)
    {
      struct answer *answer = *result;

      if (answer->count == candidate->count)
	{
	  for (i = 0; i < answer->count; i++)
	    if (! _cpp_equiv_tokens (&answer->first[i], &candidate->first[i]))
	      break;

	  if (i == answer->count)
	    break;
	}
    }

  return result;
}