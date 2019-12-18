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
struct TYPE_8__ {char node_code; int /*<<< orphan*/  node_class; int /*<<< orphan*/  lineno; } ;
struct TYPE_9__ {char const* message; TYPE_4__* child; TYPE_1__ type; } ;
struct TYPE_10__ {int /*<<< orphan*/  lineno; } ;
struct TYPE_11__ {TYPE_2__ assert_s; TYPE_3__ type; } ;
typedef  TYPE_4__ etree_type ;

/* Variables and functions */
 int /*<<< orphan*/  etree_assert ; 
 TYPE_4__* stat_alloc (int) ; 

etree_type *
exp_assert (etree_type *exp, const char *message)
{
  etree_type *n;

  n = stat_alloc (sizeof (n->assert_s));
  n->assert_s.type.node_code = '!';
  n->assert_s.type.lineno = exp->type.lineno;
  n->assert_s.type.node_class = etree_assert;
  n->assert_s.child = exp;
  n->assert_s.message = message;
  return n;
}