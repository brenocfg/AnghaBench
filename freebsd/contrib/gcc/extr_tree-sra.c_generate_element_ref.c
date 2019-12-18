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
struct sra_elt {int /*<<< orphan*/  element; struct sra_elt* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  generate_one_element_ref (struct sra_elt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
generate_element_ref (struct sra_elt *elt)
{
  if (elt->parent)
    return generate_one_element_ref (elt, generate_element_ref (elt->parent));
  else
    return elt->element;
}