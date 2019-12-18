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
struct sra_elt {int /*<<< orphan*/  element; struct sra_elt* parent; } ;
typedef  int hashval_t ;

/* Variables and functions */
 int sra_hash_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
sra_elt_hash (const void *x)
{
  const struct sra_elt *e = x;
  const struct sra_elt *p;
  hashval_t h;

  h = sra_hash_tree (e->element);

  /* Take into account everything back up the chain.  Given that chain
     lengths are rarely very long, this should be acceptable.  If we
     truly identify this as a performance problem, it should work to
     hash the pointer value "e->parent".  */
  for (p = e->parent; p ; p = p->parent)
    h = (h * 65521) ^ sra_hash_tree (p->element);

  return h;
}