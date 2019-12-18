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
struct alias {int /*<<< orphan*/  name; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__* segT ;
struct TYPE_3__ {char const* name; } ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdoutput ; 

__attribute__((used)) static void
do_secalias (const char *alias, PTR value)
{
  struct alias *h = (struct alias *) value;
  segT sec = bfd_get_section_by_name (stdoutput, h->name);

  if (sec == NULL)
    as_warn_where (h->file, h->line,
		   _("section `%s' aliased to `%s' is not used"),
		   h->name, alias);
  else
    sec->name = alias;
}