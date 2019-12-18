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
struct bin_group_icon_item {int /*<<< orphan*/  count; int /*<<< orphan*/  sig2; int /*<<< orphan*/  sig1; int /*<<< orphan*/  index; int /*<<< orphan*/  bytes; int /*<<< orphan*/  bits; int /*<<< orphan*/  planes; int /*<<< orphan*/  pad; int /*<<< orphan*/  colors; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct bin_group_icon {int /*<<< orphan*/  count; int /*<<< orphan*/  sig2; int /*<<< orphan*/  sig1; int /*<<< orphan*/  index; int /*<<< orphan*/  bytes; int /*<<< orphan*/  bits; int /*<<< orphan*/  planes; int /*<<< orphan*/  pad; int /*<<< orphan*/  colors; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_3__ {int planes; int bits; int index; int /*<<< orphan*/  bytes; int /*<<< orphan*/  colors; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct TYPE_3__* next; } ;
typedef  TYPE_1__ rc_group_icon ;

/* Variables and functions */
 scalar_t__ BIN_GROUP_ICON_ITEM_SIZE ; 
 scalar_t__ BIN_GROUP_ICON_SIZE ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,struct bin_group_icon_item*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windres_put_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_group_icon (windres_bfd *wrbfd, rc_uint_type off, const rc_group_icon *group_icons)
{
  rc_uint_type start;
  struct bin_group_icon bgi;
  int c;
  const rc_group_icon *gi;

  start = off;
  off += BIN_GROUP_ICON_SIZE;

  for (c = 0, gi = group_icons; gi != NULL; gi = gi->next, c++)
    {
      struct bin_group_icon_item bgii;

      if (wrbfd)
	{
	  windres_put_8 (wrbfd, bgii.width, gi->width);
	  windres_put_8 (wrbfd, bgii.height, gi->height);
	  windres_put_8 (wrbfd, bgii.colors, gi->colors);
	  windres_put_8 (wrbfd, bgii.pad, 0);
	  windres_put_16 (wrbfd, bgii.planes, gi->planes);
	  windres_put_16 (wrbfd, bgii.bits, gi->bits);
	  windres_put_32 (wrbfd, bgii.bytes, gi->bytes);
	  windres_put_16 (wrbfd, bgii.index, gi->index);
	  set_windres_bfd_content (wrbfd, &bgii, off, BIN_GROUP_ICON_ITEM_SIZE);
	}
      off += BIN_GROUP_ICON_ITEM_SIZE;
    }

  if (wrbfd)
    {
      windres_put_16 (wrbfd, bgi.sig1, 0);
      windres_put_16 (wrbfd, bgi.sig2, 1);
      windres_put_16 (wrbfd, bgi.count, c);
      set_windres_bfd_content (wrbfd, &bgi, start, BIN_GROUP_ICON_SIZE);
    }
  return off;
}