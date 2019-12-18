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
struct macro_scope {int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
struct macro_definition {int dummy; } ;

/* Variables and functions */
 struct macro_definition* macro_lookup_definition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

struct macro_definition *
standard_macro_lookup (const char *name, void *baton)
{
  struct macro_scope *ms = (struct macro_scope *) baton;

  return macro_lookup_definition (ms->file, ms->line, name);
}