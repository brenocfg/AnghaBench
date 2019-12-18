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
struct macro_key {int /*<<< orphan*/  table; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  macro_bcache_free (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  macro_free (struct macro_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
macro_tree_delete_key (void *untyped_key)
{
  struct macro_key *key = (struct macro_key *) untyped_key;

  macro_bcache_free (key->table, (char *) key->name);
  macro_free (key, key->table);
}