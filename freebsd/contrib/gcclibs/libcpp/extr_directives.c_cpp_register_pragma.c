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
struct TYPE_2__ {scalar_t__ handler; } ;
struct pragma_entry {int allow_expansion; TYPE_1__ u; } ;
typedef  scalar_t__ pragma_cb ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ICE ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct pragma_entry* register_pragma_1 (int /*<<< orphan*/ *,char const*,char const*,int) ; 

void
cpp_register_pragma (cpp_reader *pfile, const char *space, const char *name,
		     pragma_cb handler, bool allow_expansion)
{
  struct pragma_entry *entry;

  if (!handler)
    {
      cpp_error (pfile, CPP_DL_ICE, "registering pragma with NULL handler");
      return;
    }

  entry = register_pragma_1 (pfile, space, name, false);
  if (entry)
    {
      entry->allow_expansion = allow_expansion;
      entry->u.handler = handler;
    }
}