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
typedef  scalar_t__ tree ;
typedef  int hashval_t ;

/* Variables and functions */
 scalar_t__ TREE_HASH (scalar_t__) ; 

__attribute__((used)) static hashval_t
list_hash_pieces (tree purpose, tree value, tree chain)
{
  hashval_t hashcode = 0;

  if (chain)
    hashcode += TREE_HASH (chain);

  if (value)
    hashcode += TREE_HASH (value);
  else
    hashcode += 1007;
  if (purpose)
    hashcode += TREE_HASH (purpose);
  else
    hashcode += 1009;
  return hashcode;
}