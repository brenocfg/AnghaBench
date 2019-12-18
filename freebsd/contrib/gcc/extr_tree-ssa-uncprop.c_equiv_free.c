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
struct equiv_hash_elt {int /*<<< orphan*/  equivalences; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct equiv_hash_elt*) ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void
equiv_free (void *p)
{
  struct equiv_hash_elt *elt = (struct equiv_hash_elt *) p;
  VEC_free (tree, heap, elt->equivalences);
  free (elt);
}