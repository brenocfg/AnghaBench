#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct answer {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  node; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_1__ val; } ;
typedef  TYPE_3__ cpp_token ;
struct TYPE_12__ {int /*<<< orphan*/  prevent_expansion; } ;
struct TYPE_14__ {TYPE_2__ state; } ;
typedef  TYPE_4__ cpp_reader ;
typedef  int /*<<< orphan*/  cpp_hashnode ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_NAME ; 
 unsigned int NODE_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODE_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (unsigned int) ; 
 int /*<<< orphan*/  cpp_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* cpp_get_token (TYPE_4__*) ; 
 int /*<<< orphan*/ * cpp_lookup (TYPE_4__*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ parse_answer (TYPE_4__*,struct answer**,int) ; 

__attribute__((used)) static cpp_hashnode *
parse_assertion (cpp_reader *pfile, struct answer **answerp, int type)
{
  cpp_hashnode *result = 0;
  const cpp_token *predicate;

  /* We don't expand predicates or answers.  */
  pfile->state.prevent_expansion++;

  *answerp = 0;
  predicate = cpp_get_token (pfile);
  if (predicate->type == CPP_EOF)
    cpp_error (pfile, CPP_DL_ERROR, "assertion without predicate");
  else if (predicate->type != CPP_NAME)
    cpp_error (pfile, CPP_DL_ERROR, "predicate must be an identifier");
  else if (parse_answer (pfile, answerp, type) == 0)
    {
      unsigned int len = NODE_LEN (predicate->val.node);
      unsigned char *sym = (unsigned char *) alloca (len + 1);

      /* Prefix '#' to get it out of macro namespace.  */
      sym[0] = '#';
      memcpy (sym + 1, NODE_NAME (predicate->val.node), len);
      result = cpp_lookup (pfile, sym, len + 1);
    }

  pfile->state.prevent_expansion--;
  return result;
}