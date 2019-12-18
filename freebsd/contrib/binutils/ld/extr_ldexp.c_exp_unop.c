#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int node_code; int /*<<< orphan*/  node_class; int /*<<< orphan*/  lineno; } ;
struct TYPE_16__ {TYPE_2__ type; TYPE_5__* child; } ;
struct TYPE_17__ {int /*<<< orphan*/  lineno; } ;
struct TYPE_18__ {TYPE_3__ unary; TYPE_4__ type; } ;
typedef  TYPE_5__ etree_type ;
struct TYPE_14__ {int /*<<< orphan*/  value; scalar_t__ valid_p; } ;
struct TYPE_19__ {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  etree_unary ; 
 int /*<<< orphan*/  exp_fold_tree_no_dot (TYPE_5__*) ; 
 TYPE_5__* exp_intop (int /*<<< orphan*/ ) ; 
 TYPE_9__ expld ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_5__*,int) ; 
 TYPE_5__* stat_alloc (int) ; 

etree_type *
exp_unop (int code, etree_type *child)
{
  etree_type value, *new;

  value.unary.type.node_code = code;
  value.unary.type.lineno = child->type.lineno;
  value.unary.child = child;
  value.unary.type.node_class = etree_unary;
  exp_fold_tree_no_dot (&value);
  if (expld.result.valid_p)
    return exp_intop (expld.result.value);

  new = stat_alloc (sizeof (new->unary));
  memcpy (new, &value, sizeof (new->unary));
  return new;
}