#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unichar ;
typedef  void* rc_uint_type ;
struct TYPE_4__ {struct TYPE_4__* popup; void* help; int /*<<< orphan*/  text; void* id; void* state; void* type; int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ rc_menuitem ;

/* Variables and functions */
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  unichar_dup (int /*<<< orphan*/  const*) ; 

rc_menuitem *
define_menuitem (const unichar *text, rc_uint_type menuid, rc_uint_type type,
		 rc_uint_type state, rc_uint_type help,
		 rc_menuitem *menuitems)
{
  rc_menuitem *mi;

  mi = (rc_menuitem *) res_alloc (sizeof (rc_menuitem));
  mi->next = NULL;
  mi->type = type;
  mi->state = state;
  mi->id = menuid;
  mi->text = unichar_dup (text);
  mi->help = help;
  mi->popup = menuitems;
  return mi;
}