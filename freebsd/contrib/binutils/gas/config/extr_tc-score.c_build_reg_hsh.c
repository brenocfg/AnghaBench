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
struct reg_map {int /*<<< orphan*/ * htab; struct reg_entry* names; } ;
struct reg_entry {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_new () ; 
 int /*<<< orphan*/  insert_reg (struct reg_entry const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
build_reg_hsh (struct reg_map *map)
{
  const struct reg_entry *r;

  if ((map->htab = hash_new ()) == NULL)
    {
      as_fatal (_("virtual memory exhausted"));
    }
  for (r = map->names; r->name != NULL; r++)
    {
      insert_reg (r, map->htab);
    }
}