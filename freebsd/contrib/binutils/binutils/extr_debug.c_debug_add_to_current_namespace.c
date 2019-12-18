#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct debug_namespace {int dummy; } ;
struct debug_name {int dummy; } ;
struct debug_handle {TYPE_1__* current_file; TYPE_2__* current_block; int /*<<< orphan*/ * current_unit; } ;
typedef  enum debug_object_linkage { ____Placeholder_debug_object_linkage } debug_object_linkage ;
typedef  enum debug_object_kind { ____Placeholder_debug_object_kind } debug_object_kind ;
struct TYPE_4__ {struct debug_namespace* locals; } ;
struct TYPE_3__ {struct debug_namespace* globals; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct debug_name* debug_add_to_namespace (struct debug_handle*,struct debug_namespace**,char const*,int,int) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct debug_name *
debug_add_to_current_namespace (struct debug_handle *info, const char *name,
				enum debug_object_kind kind,
				enum debug_object_linkage linkage)
{
  struct debug_namespace **nsp;

  if (info->current_unit == NULL
      || info->current_file == NULL)
    {
      debug_error (_("debug_add_to_current_namespace: no current file"));
      return NULL;
    }

  if (info->current_block != NULL)
    nsp = &info->current_block->locals;
  else
    nsp = &info->current_file->globals;

  return debug_add_to_namespace (info, nsp, name, kind, linkage);
}