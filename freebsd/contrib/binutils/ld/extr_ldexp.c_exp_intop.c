#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  node_class; int /*<<< orphan*/  lineno; int /*<<< orphan*/  node_code; } ;
struct TYPE_6__ {int /*<<< orphan*/ * str; int /*<<< orphan*/  value; } ;
struct TYPE_8__ {TYPE_2__ type; TYPE_1__ value; } ;
typedef  TYPE_3__ etree_type ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/  INT ; 
 int /*<<< orphan*/  etree_value ; 
 int /*<<< orphan*/  lineno ; 
 TYPE_3__* stat_alloc (int) ; 

etree_type *
exp_intop (bfd_vma value)
{
  etree_type *new = stat_alloc (sizeof (new->value));
  new->type.node_code = INT;
  new->type.lineno = lineno;
  new->value.value = value;
  new->value.str = NULL;
  new->type.node_class = etree_value;
  return new;
}