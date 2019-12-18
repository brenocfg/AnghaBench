#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct builtin {int /*<<< orphan*/  value; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_3__ {int /*<<< orphan*/  directive_index; scalar_t__ is_directive; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ cpp_hashnode ;

/* Variables and functions */
 int ARRAY_SIZE (struct builtin const*) ; 
 int /*<<< orphan*/  NODE_OPERATOR ; 
 TYPE_1__* cpp_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct builtin const* operator_array ; 

__attribute__((used)) static void
mark_named_operators (cpp_reader *pfile)
{
  const struct builtin *b;

  for (b = operator_array;
       b < (operator_array + ARRAY_SIZE (operator_array));
       b++)
    {
      cpp_hashnode *hp = cpp_lookup (pfile, b->name, b->len);
      hp->flags |= NODE_OPERATOR;
      hp->is_directive = 0;
      hp->directive_index = b->value;
    }
}