#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* varinfo_t ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {unsigned int id; char const* name; int directly_dereferenced; int is_artificial_var; int is_heap_var; int is_special_var; int is_unknown_size_var; int has_union; int /*<<< orphan*/ * collapsed_to; int /*<<< orphan*/ * next; void* oldsolution; void* solution; int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 void* BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oldpta_obstack ; 
 TYPE_1__* pool_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pta_obstack ; 
 int /*<<< orphan*/  variable_info_pool ; 

__attribute__((used)) static varinfo_t
new_var_info (tree t, unsigned int id, const char *name)
{
  varinfo_t ret = pool_alloc (variable_info_pool);

  ret->id = id;
  ret->name = name;
  ret->decl = t;
  ret->directly_dereferenced = false;
  ret->is_artificial_var = false;
  ret->is_heap_var = false;
  ret->is_special_var = false;
  ret->is_unknown_size_var = false;
  ret->has_union = false;
  ret->solution = BITMAP_ALLOC (&pta_obstack);
  ret->oldsolution = BITMAP_ALLOC (&oldpta_obstack);
  ret->next = NULL;
  ret->collapsed_to = NULL;
  return ret;
}