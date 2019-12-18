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
struct TYPE_2__ {int /*<<< orphan*/  handler; } ;
struct pragma_entry {int is_internal; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  pragma_cb ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 struct pragma_entry* register_pragma_1 (int /*<<< orphan*/ *,char const*,char const*,int) ; 

__attribute__((used)) static void
register_pragma_internal (cpp_reader *pfile, const char *space,
			  const char *name, pragma_cb handler)
{
  struct pragma_entry *entry;

  entry = register_pragma_1 (pfile, space, name, false);
  entry->is_internal = true;
  entry->u.handler = handler;
}