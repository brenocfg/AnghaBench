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
typedef  int hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_NAME (int /*<<< orphan*/ ) ; 
 int htab_hash_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
typename_hash (const void* k)
{
  hashval_t hash;
  tree t = (tree) k;

  hash = (htab_hash_pointer (TYPE_CONTEXT (t))
	  ^ htab_hash_pointer (DECL_NAME (TYPE_NAME (t))));

  return hash;
}