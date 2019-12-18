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
struct type {int dummy; } ;

/* Variables and functions */
 struct type* basic_lookup_transparent_type (char const*) ; 
 char* block_scope (int /*<<< orphan*/ ) ; 
 struct type* cp_lookup_transparent_type_loop (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ ) ; 

struct type *
cp_lookup_transparent_type (const char *name)
{
  /* First, try the honest way of looking up the definition.  */
  struct type *t = basic_lookup_transparent_type (name);
  const char *scope;

  if (t != NULL)
    return t;

  /* If that doesn't work and we're within a namespace, look there
     instead.  */
  scope = block_scope (get_selected_block (0));

  if (scope[0] == '\0')
    return NULL;

  return cp_lookup_transparent_type_loop (name, scope, 0);
}