#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
struct bin_group_cursor_item {int /*<<< orphan*/  nitems; int /*<<< orphan*/  sig2; int /*<<< orphan*/  sig1; int /*<<< orphan*/  index; int /*<<< orphan*/  bytes; int /*<<< orphan*/  bits; int /*<<< orphan*/  planes; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct bin_group_cursor {int /*<<< orphan*/  nitems; int /*<<< orphan*/  sig2; int /*<<< orphan*/  sig1; int /*<<< orphan*/  index; int /*<<< orphan*/  bytes; int /*<<< orphan*/  bits; int /*<<< orphan*/  planes; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_3__ {int width; int height; int planes; int bits; int index; int /*<<< orphan*/  bytes; struct TYPE_3__* next; } ;
typedef  TYPE_1__ rc_group_cursor ;

/* Variables and functions */
 scalar_t__ BIN_GROUP_CURSOR_ITEM_SIZE ; 
 scalar_t__ BIN_GROUP_CURSOR_SIZE ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,struct bin_group_cursor_item*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_group_cursor (windres_bfd *wrbfd, rc_uint_type off,
			 const rc_group_cursor *group_cursors)
{
  int c = 0;
  const rc_group_cursor *gc;
  struct bin_group_cursor bgc;
  struct bin_group_cursor_item bgci;
  rc_uint_type start = off;

  off += BIN_GROUP_CURSOR_SIZE;

  for (c = 0, gc = group_cursors; gc != NULL; gc = gc->next, c++)
    {
      if (wrbfd)
	{
	  windres_put_16 (wrbfd, bgci.width, gc->width);
	  windres_put_16 (wrbfd, bgci.height, gc->height);
	  windres_put_16 (wrbfd, bgci.planes, gc->planes);
	  windres_put_16 (wrbfd, bgci.bits, gc->bits);
	  windres_put_32 (wrbfd, bgci.bytes, gc->bytes);
	  windres_put_16 (wrbfd, bgci.index, gc->index);
	  set_windres_bfd_content (wrbfd, &bgci, off, BIN_GROUP_CURSOR_ITEM_SIZE);
    }

      off += BIN_GROUP_CURSOR_ITEM_SIZE;
    }
  if (wrbfd)
    {
      windres_put_16 (wrbfd, bgc.sig1, 0);
      windres_put_16 (wrbfd, bgc.sig2, 2);
      windres_put_16 (wrbfd, bgc.nitems, c);
      set_windres_bfd_content (wrbfd, &bgc, start, BIN_GROUP_CURSOR_SIZE);
    }
  return off;
}