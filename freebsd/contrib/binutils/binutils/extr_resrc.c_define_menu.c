#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  language; } ;
struct TYPE_7__ {TYPE_4__* menu; } ;
struct TYPE_8__ {TYPE_3__ res_info; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ rc_res_resource ;
typedef  TYPE_3__ rc_res_res_info ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_menuitem ;
struct TYPE_10__ {scalar_t__ help; int /*<<< orphan*/ * items; } ;
typedef  TYPE_4__ rc_menu ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_MENU ; 
 int /*<<< orphan*/  RT_MENU ; 
 TYPE_2__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 

void
define_menu (rc_res_id id, const rc_res_res_info *resinfo,
	     rc_menuitem *menuitems)
{
  rc_menu *m;
  rc_res_resource *r;

  m = (rc_menu *) res_alloc (sizeof (rc_menu));
  m->items = menuitems;
  m->help = 0;

  r = define_standard_resource (&resources, RT_MENU, id, resinfo->language, 0);
  r->type = RES_TYPE_MENU;
  r->u.menu = m;
  r->res_info = *resinfo;
}