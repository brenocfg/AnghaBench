#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  int /*<<< orphan*/  rc_uint_type ;
typedef  int /*<<< orphan*/  rc_res_resource ;
struct TYPE_4__ {int id; } ;
struct TYPE_5__ {TYPE_1__ u; scalar_t__ named; } ;
typedef  TYPE_2__ rc_res_id ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_BITMAP ; 
 int /*<<< orphan*/  RES_TYPE_FONT ; 
 int /*<<< orphan*/  RES_TYPE_ICON ; 
 int /*<<< orphan*/  RES_TYPE_MESSAGETABLE ; 
 int /*<<< orphan*/  RES_TYPE_RCDATA ; 
#define  RT_ACCELERATOR 142 
#define  RT_BITMAP 141 
#define  RT_CURSOR 140 
#define  RT_DIALOG 139 
#define  RT_FONT 138 
#define  RT_FONTDIR 137 
#define  RT_GROUP_CURSOR 136 
#define  RT_GROUP_ICON 135 
#define  RT_ICON 134 
#define  RT_MENU 133 
#define  RT_MESSAGETABLE 132 
#define  RT_RCDATA 131 
#define  RT_STRING 130 
#define  RT_TOOLBAR 129 
#define  RT_VERSION 128 
 int /*<<< orphan*/ * bin_to_res_accelerators (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_dialog (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_fontdir (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_group_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_group_icon (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_menu (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_rcdata (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_toolbar (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_userdata (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bin_to_res_version (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

rc_res_resource *
bin_to_res (windres_bfd *wrbfd, rc_res_id type, const bfd_byte *data,
	    rc_uint_type length)
{
  if (type.named)
    return bin_to_res_userdata (wrbfd, data, length);
  else
    {
      switch (type.u.id)
	{
	default:
	  return bin_to_res_userdata (wrbfd, data, length);
	case RT_CURSOR:
	  return bin_to_res_cursor (wrbfd, data, length);
	case RT_BITMAP:
	  return bin_to_res_generic (wrbfd, RES_TYPE_BITMAP, data, length);
	case RT_ICON:
	  return bin_to_res_generic (wrbfd, RES_TYPE_ICON, data, length);
	case RT_MENU:
	  return bin_to_res_menu (wrbfd, data, length);
	case RT_DIALOG:
	  return bin_to_res_dialog (wrbfd, data, length);
	case RT_STRING:
	  return bin_to_res_string (wrbfd, data, length);
	case RT_FONTDIR:
	  return bin_to_res_fontdir (wrbfd, data, length);
	case RT_FONT:
	  return bin_to_res_generic (wrbfd, RES_TYPE_FONT, data, length);
	case RT_ACCELERATOR:
	  return bin_to_res_accelerators (wrbfd, data, length);
	case RT_RCDATA:
	  return bin_to_res_rcdata (wrbfd, data, length, RES_TYPE_RCDATA);
	case RT_MESSAGETABLE:
	  return bin_to_res_generic (wrbfd, RES_TYPE_MESSAGETABLE, data, length);
	case RT_GROUP_CURSOR:
	  return bin_to_res_group_cursor (wrbfd, data, length);
	case RT_GROUP_ICON:
	  return bin_to_res_group_icon (wrbfd, data, length);
	case RT_VERSION:
	  return bin_to_res_version (wrbfd, data, length);
	case RT_TOOLBAR:
	  return  bin_to_res_toolbar (wrbfd, data, length);

	}
    }
}