#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct answer {int dummy; } ;
struct TYPE_10__ {TYPE_1__* cur_token; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_11__ {scalar_t__ type; } ;
typedef  TYPE_3__ cpp_hashnode ;
struct TYPE_9__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CPP_EOF ; 
 scalar_t__ NT_ASSERTION ; 
 int /*<<< orphan*/  T_IF ; 
 int /*<<< orphan*/  _cpp_backup_tokens (TYPE_2__*,int) ; 
 scalar_t__* find_answer (TYPE_3__*,struct answer*) ; 
 TYPE_3__* parse_assertion (TYPE_2__*,struct answer**,int /*<<< orphan*/ ) ; 

int
_cpp_test_assertion (cpp_reader *pfile, unsigned int *value)
{
  struct answer *answer;
  cpp_hashnode *node;

  node = parse_assertion (pfile, &answer, T_IF);

  /* For recovery, an erroneous assertion expression is handled as a
     failing assertion.  */
  *value = 0;

  if (node)
    *value = (node->type == NT_ASSERTION &&
	      (answer == 0 || *find_answer (node, answer) != 0));
  else if (pfile->cur_token[-1].type == CPP_EOF)
    _cpp_backup_tokens (pfile, 1);

  /* We don't commit the memory for the answer - it's temporary only.  */
  return node == 0;
}