#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_45__ {int language; } ;
struct TYPE_43__ {TYPE_8__* userdata; } ;
struct TYPE_44__ {TYPE_6__ res_info; TYPE_4__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ rc_res_resource ;
typedef  TYPE_6__ rc_res_res_info ;
struct TYPE_40__ {int id; } ;
struct TYPE_46__ {scalar_t__ named; TYPE_1__ u; } ;
typedef  TYPE_7__ rc_res_id ;
struct TYPE_41__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
struct TYPE_42__ {TYPE_2__ buffer; } ;
struct TYPE_47__ {TYPE_3__ u; int /*<<< orphan*/  type; int /*<<< orphan*/ * next; } ;
typedef  TYPE_8__ rc_rcdata_item ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RCDATA_BUFFER ; 
 int /*<<< orphan*/  RES_TYPE_USERDATA ; 
#define  RT_BITMAP 135 
#define  RT_CURSOR 134 
#define  RT_FONT 133 
#define  RT_FONTDIR 132 
#define  RT_GROUP_CURSOR 131 
#define  RT_GROUP_ICON 130 
#define  RT_ICON 129 
#define  RT_MESSAGETABLE 128 
 int /*<<< orphan*/  define_bitmap_rcdata (TYPE_7__,TYPE_6__ const*,TYPE_8__*) ; 
 int /*<<< orphan*/  define_cursor_rcdata (TYPE_7__,TYPE_6__ const*,TYPE_8__*) ; 
 int /*<<< orphan*/  define_font_rcdata (TYPE_7__,TYPE_6__ const*,TYPE_8__*) ; 
 int /*<<< orphan*/  define_fontdir_rcdata (TYPE_7__,TYPE_6__ const*,TYPE_8__*) ; 
 int /*<<< orphan*/  define_group_cursor_rcdata (TYPE_7__,TYPE_6__ const*,TYPE_8__*) ; 
 int /*<<< orphan*/  define_group_icon_rcdata (TYPE_7__,TYPE_6__ const*,TYPE_8__*) ; 
 int /*<<< orphan*/  define_icon_rcdata (TYPE_7__,TYPE_6__ const*,TYPE_8__*) ; 
 int /*<<< orphan*/  define_messagetable_rcdata (TYPE_7__,TYPE_6__ const*,TYPE_8__*) ; 
 TYPE_5__* define_resource (int /*<<< orphan*/ *,int,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rcdata_render_as_buffer (TYPE_8__*,int /*<<< orphan*/ *) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 

void
define_user_data (rc_res_id id, rc_res_id type,
		  const rc_res_res_info *resinfo,
		  rc_rcdata_item *data)
{
  rc_res_id ids[3];
  rc_res_resource *r;
  bfd_byte *pb_data;
  rc_uint_type len_data;

  /* We have to check if the binary data is parsed specially.  */
  if (type.named == 0)
    {
      switch (type.u.id)
      {
      case RT_FONTDIR:
	define_fontdir_rcdata (id, resinfo, data);
	return;
      case RT_FONT:
	define_font_rcdata (id, resinfo, data);
	return;
      case RT_ICON:
	define_icon_rcdata (id, resinfo, data);
	return;
      case RT_BITMAP:
	define_bitmap_rcdata (id, resinfo, data);
	return;
      case RT_CURSOR:
	define_cursor_rcdata (id, resinfo, data);
	return;
      case RT_GROUP_ICON:
	define_group_icon_rcdata (id, resinfo, data);
	return;
      case RT_GROUP_CURSOR:
	define_group_cursor_rcdata (id, resinfo, data);
	return;
      case RT_MESSAGETABLE:
	define_messagetable_rcdata (id, resinfo, data);
	return;
      default:
	/* Treat as normal user-data.  */
	break;
      }
    }
  ids[0] = type;
  ids[1] = id;
  ids[2].named = 0;
  ids[2].u.id = resinfo->language;

  r = define_resource (& resources, 3, ids, 0);
  r->type = RES_TYPE_USERDATA;
  r->u.userdata = ((rc_rcdata_item *)
		   res_alloc (sizeof (rc_rcdata_item)));
  r->u.userdata->next = NULL;
  r->u.userdata->type = RCDATA_BUFFER;
  pb_data = rcdata_render_as_buffer (data, &len_data);
  r->u.userdata->u.buffer.length = len_data;
  r->u.userdata->u.buffer.data = pb_data;
  r->res_info = *resinfo;
}