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
struct pr_handle {TYPE_1__* stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char*) ; 

__attribute__((used)) static bfd_boolean
pr_pointer_type (void *p)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *s;

  assert (info->stack != NULL);

  s = strchr (info->stack->type, '|');
  if (s != NULL && s[1] == '[')
    return substitute_type (info, "(*|)");
  return substitute_type (info, "*|");
}