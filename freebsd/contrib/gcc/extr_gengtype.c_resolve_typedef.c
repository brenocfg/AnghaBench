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
typedef  int /*<<< orphan*/  type_p ;
struct fileloc {int dummy; } ;
typedef  TYPE_1__* pair_p ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_scalar_type (char*,int) ; 
 int /*<<< orphan*/  error_at_line (struct fileloc*,char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* typedefs ; 

type_p
resolve_typedef (const char *s, struct fileloc *pos)
{
  pair_p p;
  for (p = typedefs; p != NULL; p = p->next)
    if (strcmp (p->name, s) == 0)
      return p->type;
  error_at_line (pos, "unidentified type `%s'", s);
  return create_scalar_type ("char", 4);
}