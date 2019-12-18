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
struct stab_handle {char const* main_filename; struct bincl_file* bincl_stack; int /*<<< orphan*/ * file_types; } ;
struct bincl_file {size_t file; char const* name; int /*<<< orphan*/  file_types; struct bincl_file* next_stack; } ;

/* Variables and functions */

__attribute__((used)) static const char *
pop_bincl (struct stab_handle *info)
{
  struct bincl_file *o;

  o = info->bincl_stack;
  if (o == NULL)
    return info->main_filename;
  info->bincl_stack = o->next_stack;

  o->file_types = info->file_types[o->file];

  if (info->bincl_stack == NULL)
    return info->main_filename;
  return info->bincl_stack->name;
}