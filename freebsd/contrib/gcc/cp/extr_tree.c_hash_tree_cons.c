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
typedef  void* tree ;
struct list_proxy {void* chain; void* value; void* purpose; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,struct list_proxy*,int,int /*<<< orphan*/ ) ; 
 int list_hash_pieces (void*,void*,void*) ; 
 int /*<<< orphan*/  list_hash_table ; 
 void* tree_cons (void*,void*,void*) ; 

tree
hash_tree_cons (tree purpose, tree value, tree chain)
{
  int hashcode = 0;
  void **slot;
  struct list_proxy proxy;

  /* Hash the list node.  */
  hashcode = list_hash_pieces (purpose, value, chain);
  /* Create a proxy for the TREE_LIST we would like to create.  We
     don't actually create it so as to avoid creating garbage.  */
  proxy.purpose = purpose;
  proxy.value = value;
  proxy.chain = chain;
  /* See if it is already in the table.  */
  slot = htab_find_slot_with_hash (list_hash_table, &proxy, hashcode,
				   INSERT);
  /* If not, create a new node.  */
  if (!*slot)
    *slot = tree_cons (purpose, value, chain);
  return (tree) *slot;
}