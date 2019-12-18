#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* rc_uint_type ;
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_2__ rc_toolbar_item ;
struct TYPE_11__ {scalar_t__ nitems; TYPE_2__* items; void* button_height; void* button_width; } ;
typedef  TYPE_3__ rc_toolbar ;
struct TYPE_13__ {int /*<<< orphan*/  language; } ;
struct TYPE_9__ {TYPE_3__* toolbar; } ;
struct TYPE_12__ {TYPE_5__ res_info; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ rc_res_resource ;
typedef  TYPE_5__ rc_res_res_info ;
typedef  int /*<<< orphan*/  rc_res_id ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_TOOLBAR ; 
 int /*<<< orphan*/  RT_TOOLBAR ; 
 TYPE_4__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 

void
define_toolbar (rc_res_id id, rc_res_res_info *resinfo, rc_uint_type width, rc_uint_type height,
		rc_toolbar_item *items)
{
  rc_toolbar *t;
  rc_res_resource *r;

  t = (rc_toolbar *) res_alloc (sizeof (rc_toolbar));
  t->button_width = width;
  t->button_height = height;
  t->nitems = 0;
  t->items = items;
  while (items != NULL)
  {
    t->nitems+=1;
    items = items->next;
  }
  r = define_standard_resource (&resources, RT_TOOLBAR, id, resinfo->language, 0);
  r->type = RES_TYPE_TOOLBAR;
  r->u.toolbar = t;
  r->res_info = *resinfo;
}