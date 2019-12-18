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
typedef  int /*<<< orphan*/ * tree ;
struct int_tree_map {unsigned int uid; int /*<<< orphan*/ * to; } ;

/* Variables and functions */
 int /*<<< orphan*/  complex_variable_components ; 
 struct int_tree_map* htab_find_with_hash (int /*<<< orphan*/ ,struct int_tree_map*,unsigned int) ; 

__attribute__((used)) static tree 
cvc_lookup (unsigned int uid)
{
  struct int_tree_map *h, in;
  in.uid = uid;
  h = htab_find_with_hash (complex_variable_components, &in, uid);
  return h ? h->to : NULL;
}