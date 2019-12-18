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
typedef  int /*<<< orphan*/  tree ;
struct tree_int_map {unsigned short to; int /*<<< orphan*/  from; } ;

/* Variables and functions */
 struct tree_int_map* htab_find_with_hash (int /*<<< orphan*/ ,struct tree_int_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_priority_for_decl ; 

unsigned short
decl_init_priority_lookup (tree from)
{
  struct tree_int_map *h, in;
  in.from = from;

  h = htab_find_with_hash (init_priority_for_decl, 
			   &in, htab_hash_pointer (from));
  if (h)
    return h->to;
  return 0;
}