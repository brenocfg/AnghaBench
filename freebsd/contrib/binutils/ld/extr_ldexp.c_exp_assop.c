#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* dst; TYPE_3__* src; } ;
struct TYPE_8__ {int node_code; int /*<<< orphan*/  node_class; int /*<<< orphan*/  lineno; } ;
struct TYPE_9__ {TYPE_1__ assign; TYPE_2__ type; } ;
typedef  TYPE_3__ etree_type ;

/* Variables and functions */
 int /*<<< orphan*/  etree_assign ; 
 TYPE_3__* stat_alloc (int) ; 

etree_type *
exp_assop (int code, const char *dst, etree_type *src)
{
  etree_type *new;

  new = stat_alloc (sizeof (new->assign));
  new->type.node_code = code;
  new->type.lineno = src->type.lineno;
  new->type.node_class = etree_assign;
  new->assign.src = src;
  new->assign.dst = dst;
  return new;
}