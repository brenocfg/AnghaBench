#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  int rc_uint_type ;
struct TYPE_8__ {int id; } ;
struct TYPE_9__ {TYPE_1__ u; scalar_t__ named; } ;
struct TYPE_11__ {struct TYPE_11__* next; struct TYPE_11__* prev; TYPE_2__ id; } ;
typedef  TYPE_4__ rc_toolbar_item ;
struct TYPE_12__ {int nitems; TYPE_4__* items; void* button_height; void* button_width; } ;
typedef  TYPE_5__ rc_toolbar ;
struct TYPE_10__ {TYPE_5__* toolbar; } ;
struct TYPE_13__ {TYPE_3__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_6__ rc_res_resource ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_TOOLBAR ; 
 scalar_t__ res_alloc (int) ; 
 void* windres_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static rc_res_resource *
bin_to_res_toolbar (windres_bfd *wrbfd, const bfd_byte *data, rc_uint_type length)
{
  rc_toolbar *ri;
  rc_res_resource *r;
  rc_uint_type i;

  ri = (rc_toolbar *) res_alloc (sizeof (rc_toolbar));
  ri->button_width = windres_get_32 (wrbfd, data, 4);
  ri->button_height = windres_get_32 (wrbfd, data + 4, 4);
  ri->nitems = windres_get_32 (wrbfd, data + 8, 4);
  ri->items = NULL;

  data += 12;
  length -= 12;
  for (i=0 ; i < ri->nitems; i++)
  {
    rc_toolbar_item *it;
    it = (rc_toolbar_item *) res_alloc (sizeof (rc_toolbar_item));
    it->id.named = 0;
    it->id.u.id = (int) windres_get_32 (wrbfd, data, 4);
    it->prev = it->next = NULL;
    data += 4;
    length -= 4;
    if(ri->items) {
      rc_toolbar_item *ii = ri->items;
      while (ii->next != NULL)
	ii = ii->next;
      it->prev = ii;
      ii->next = it;
    }
    else
      ri->items = it;
  }
  r = (rc_res_resource *) res_alloc (sizeof *r);
  r->type = RES_TYPE_TOOLBAR;
  r->u.toolbar = ri;
  return r;
}