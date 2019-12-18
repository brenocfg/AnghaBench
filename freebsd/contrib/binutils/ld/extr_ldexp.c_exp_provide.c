#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char node_code; int /*<<< orphan*/  node_class; int /*<<< orphan*/  lineno; } ;
struct TYPE_9__ {char const* dst; int /*<<< orphan*/  hidden; TYPE_4__* src; TYPE_3__ type; } ;
struct TYPE_8__ {int /*<<< orphan*/  lineno; } ;
struct TYPE_11__ {TYPE_2__ assign; TYPE_1__ type; } ;
typedef  TYPE_4__ etree_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  etree_provide ; 
 TYPE_4__* stat_alloc (int) ; 

etree_type *
exp_provide (const char *dst, etree_type *src, bfd_boolean hidden)
{
  etree_type *n;

  n = stat_alloc (sizeof (n->assign));
  n->assign.type.node_code = '=';
  n->assign.type.lineno = src->type.lineno;
  n->assign.type.node_class = etree_provide;
  n->assign.src = src;
  n->assign.dst = dst;
  n->assign.hidden = hidden;
  return n;
}