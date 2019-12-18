#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct answer {struct answer* next; } ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_6__ {scalar_t__ answers; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ value; } ;
typedef  TYPE_2__ cpp_hashnode ;

/* Variables and functions */
 scalar_t__ NT_ASSERTION ; 
 scalar_t__ NT_VOID ; 
 int /*<<< orphan*/  T_UNASSERT ; 
 int /*<<< orphan*/  _cpp_free_definition (TYPE_2__*) ; 
 int /*<<< orphan*/  check_eol (int /*<<< orphan*/ *) ; 
 struct answer** find_answer (TYPE_2__*,struct answer*) ; 
 TYPE_2__* parse_assertion (int /*<<< orphan*/ *,struct answer**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_unassert (cpp_reader *pfile)
{
  cpp_hashnode *node;
  struct answer *answer;

  node = parse_assertion (pfile, &answer, T_UNASSERT);
  /* It isn't an error to #unassert something that isn't asserted.  */
  if (node && node->type == NT_ASSERTION)
    {
      if (answer)
	{
	  struct answer **p = find_answer (node, answer), *temp;

	  /* Remove the answer from the list.  */
	  temp = *p;
	  if (temp)
	    *p = temp->next;

	  /* Did we free the last answer?  */
	  if (node->value.answers == 0)
	    node->type = NT_VOID;

	  check_eol (pfile);
	}
      else
	_cpp_free_definition (node);
    }

  /* We don't commit the memory for the answer - it's temporary only.  */
}