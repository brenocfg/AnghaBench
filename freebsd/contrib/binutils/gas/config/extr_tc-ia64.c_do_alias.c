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
typedef  int /*<<< orphan*/  symbolS ;
struct alias {int /*<<< orphan*/  name; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 int /*<<< orphan*/  S_SET_NAME (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * symbol_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_alias (const char *alias, PTR value)
{
  struct alias *h = (struct alias *) value;
  symbolS *sym = symbol_find (h->name);

  if (sym == NULL)
    as_warn_where (h->file, h->line,
		   _("symbol `%s' aliased to `%s' is not used"),
		   h->name, alias);
    else
      S_SET_NAME (sym, (char *) alias);
}