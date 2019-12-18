#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bin_fontdir_item {scalar_t__ device_name; int /*<<< orphan*/ * index; } ;
typedef  scalar_t__ rc_uint_type ;
struct TYPE_5__ {TYPE_3__* fontdir; } ;
struct TYPE_6__ {int /*<<< orphan*/  res_info; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ rc_res_resource ;
typedef  int /*<<< orphan*/  rc_res_res_info ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_rcdata_item ;
struct TYPE_7__ {struct TYPE_7__* next; scalar_t__ length; int /*<<< orphan*/ * data; void* index; } ;
typedef  TYPE_3__ rc_fontdir ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_FONTDIR ; 
 int /*<<< orphan*/  RT_FONTDIR ; 
 TYPE_2__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rcdata_render_as_buffer (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 
 int strlen (char*) ; 
 void* windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wrtarget ; 

__attribute__((used)) static void
define_fontdir_rcdata (rc_res_id id,const rc_res_res_info *resinfo,
		       rc_rcdata_item *data)
{
  rc_res_resource *r;
  rc_fontdir *fd, *fd_first, *fd_cur;
  rc_uint_type len_data;
  bfd_byte *pb_data;
  rc_uint_type c;

  fd_cur = fd_first = NULL;
  r = define_standard_resource (&resources, RT_FONTDIR, id, 0x409, 0);

  pb_data = rcdata_render_as_buffer (data, &len_data);

  if (pb_data)
    {
      rc_uint_type off = 2;
      c = windres_get_16 (&wrtarget, pb_data, len_data);
      for (; c > 0; c--)
	{
	  size_t len;
	  rc_uint_type safe_pos = off;
	  const struct bin_fontdir_item *bfi;

	  bfi = (const struct bin_fontdir_item *) pb_data + off;
	  fd = (rc_fontdir *) res_alloc (sizeof (rc_fontdir));
	  fd->index = windres_get_16 (&wrtarget, bfi->index, len_data - off);
	  fd->data = pb_data + off;
	  off += 56;
	  len = strlen ((char *) bfi->device_name) + 1;
	  off += (rc_uint_type) len;
	  off += (rc_uint_type) strlen ((char *) bfi->device_name + len) + 1;
	  fd->length = (off - safe_pos);
	  fd->next = NULL;
	  if (fd_first == NULL)
	    fd_first = fd;
	  else
	    fd_cur->next = fd;
	  fd_cur = fd;
	}
    }
  r->type = RES_TYPE_FONTDIR;
  r->u.fontdir = fd_first;
  r->res_info = *resinfo;
}