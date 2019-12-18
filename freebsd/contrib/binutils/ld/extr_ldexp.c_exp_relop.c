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
struct TYPE_7__ {int /*<<< orphan*/  value; int /*<<< orphan*/ * section; } ;
struct TYPE_6__ {int /*<<< orphan*/  node_class; int /*<<< orphan*/  lineno; int /*<<< orphan*/  node_code; } ;
struct TYPE_8__ {TYPE_2__ rel; TYPE_1__ type; } ;
typedef  TYPE_3__ etree_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  REL ; 
 int /*<<< orphan*/  etree_rel ; 
 int /*<<< orphan*/  lineno ; 
 TYPE_3__* stat_alloc (int) ; 

etree_type *
exp_relop (asection *section, bfd_vma value)
{
  etree_type *new = stat_alloc (sizeof (new->rel));
  new->type.node_code = REL;
  new->type.lineno = lineno;
  new->type.node_class = etree_rel;
  new->rel.section = section;
  new->rel.value = value;
  return new;
}