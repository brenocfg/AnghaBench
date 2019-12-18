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
typedef  int rc_uint_type ;
struct TYPE_9__ {int /*<<< orphan*/  language; } ;
struct TYPE_7__ {TYPE_4__* group_cursor; } ;
struct TYPE_8__ {TYPE_3__ res_info; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ rc_res_resource ;
typedef  TYPE_3__ rc_res_res_info ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_rcdata_item ;
struct TYPE_10__ {struct TYPE_10__* next; void* index; int /*<<< orphan*/  bytes; void* bits; void* planes; void* height; void* width; } ;
typedef  TYPE_4__ rc_group_cursor ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_GROUP_CURSOR ; 
 int /*<<< orphan*/  RT_GROUP_ICON ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/ * rcdata_render_as_buffer (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 
 void* windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  windres_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wrtarget ; 

__attribute__((used)) static void
define_group_cursor_rcdata (rc_res_id id, const rc_res_res_info *resinfo,
			    rc_rcdata_item *data)
{
  rc_res_resource *r;
  rc_group_cursor *cg, *first, *cur;
  rc_uint_type len_data;
  bfd_byte *pb_data;

  pb_data = rcdata_render_as_buffer (data, &len_data);

  first = cur = NULL;

  while (len_data >= 6)
    {
      int c, i;
      unsigned short type;
      type = windres_get_16 (&wrtarget, pb_data + 2, len_data - 2);
      if (type != 2)
	fatal (_("unexpected group cursor type %d"), type);
      c = windres_get_16 (&wrtarget, pb_data + 4, len_data - 4);
      len_data -= 6;
      pb_data += 6;

      for (i = 0; i < c; i++)
	{
	  if (len_data < 14)
	    fatal ("too small group icon rcdata");
	  cg = (rc_group_cursor *) res_alloc (sizeof (rc_group_cursor));
	  cg->next = NULL;
	  cg->width = windres_get_16 (&wrtarget, pb_data, len_data);
	  cg->height = windres_get_16 (&wrtarget, pb_data + 2, len_data - 2);
	  cg->planes = windres_get_16 (&wrtarget, pb_data + 4, len_data - 4);
	  cg->bits =  windres_get_16 (&wrtarget, pb_data + 6, len_data - 6);
	  cg->bytes = windres_get_32 (&wrtarget, pb_data + 8, len_data - 8);
	  cg->index = windres_get_16 (&wrtarget, pb_data + 12, len_data - 12);
	  if (! first)
	    first = cg;
	  else
	    cur->next = cg;
	  cur = cg;
	  pb_data += 14;
	  len_data -= 14;
	}
    }

  r = define_standard_resource (&resources, RT_GROUP_ICON, id,
				resinfo->language, 0);
  r->type = RES_TYPE_GROUP_CURSOR;
  r->u.group_cursor = first;
  r->res_info = *resinfo;
}