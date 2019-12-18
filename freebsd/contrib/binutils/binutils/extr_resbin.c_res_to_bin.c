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
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_6__ {int /*<<< orphan*/  rcdata; int /*<<< orphan*/  toolbar; int /*<<< orphan*/  versioninfo; int /*<<< orphan*/  stringtable; int /*<<< orphan*/  menu; int /*<<< orphan*/  group_icon; int /*<<< orphan*/  fontdir; int /*<<< orphan*/  dialog; int /*<<< orphan*/  group_cursor; int /*<<< orphan*/  cursor; int /*<<< orphan*/  acc; TYPE_1__ data; } ;
struct TYPE_7__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ rc_res_resource ;

/* Variables and functions */
#define  RES_TYPE_ACCELERATOR 143 
#define  RES_TYPE_BITMAP 142 
#define  RES_TYPE_CURSOR 141 
#define  RES_TYPE_DIALOG 140 
#define  RES_TYPE_FONT 139 
#define  RES_TYPE_FONTDIR 138 
#define  RES_TYPE_GROUP_CURSOR 137 
#define  RES_TYPE_GROUP_ICON 136 
#define  RES_TYPE_ICON 135 
#define  RES_TYPE_MENU 134 
#define  RES_TYPE_MESSAGETABLE 133 
#define  RES_TYPE_RCDATA 132 
#define  RES_TYPE_STRINGTABLE 131 
#define  RES_TYPE_TOOLBAR 130 
#define  RES_TYPE_USERDATA 129 
#define  RES_TYPE_VERSIONINFO 128 
 int /*<<< orphan*/  res_to_bin_accelerator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_dialog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_fontdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_group_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_group_icon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_menu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_rcdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_stringtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_toolbar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_to_bin_versioninfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rc_uint_type
res_to_bin (windres_bfd *wrbfd, rc_uint_type off, const rc_res_resource *res)
{
  switch (res->type)
    {
    case RES_TYPE_BITMAP:
    case RES_TYPE_FONT:
    case RES_TYPE_ICON:
    case RES_TYPE_MESSAGETABLE:
      return res_to_bin_generic (wrbfd, off, res->u.data.length, res->u.data.data);
    case RES_TYPE_ACCELERATOR:
      return res_to_bin_accelerator (wrbfd, off, res->u.acc);
    case RES_TYPE_CURSOR:
      return res_to_bin_cursor (wrbfd, off, res->u.cursor);
    case RES_TYPE_GROUP_CURSOR:
      return res_to_bin_group_cursor (wrbfd, off, res->u.group_cursor);
    case RES_TYPE_DIALOG:
      return res_to_bin_dialog (wrbfd, off, res->u.dialog);
    case RES_TYPE_FONTDIR:
      return res_to_bin_fontdir (wrbfd, off, res->u.fontdir);
    case RES_TYPE_GROUP_ICON:
      return res_to_bin_group_icon (wrbfd, off, res->u.group_icon);
    case RES_TYPE_MENU:
      return res_to_bin_menu (wrbfd, off, res->u.menu);
    case RES_TYPE_STRINGTABLE:
      return res_to_bin_stringtable (wrbfd, off, res->u.stringtable);
    case RES_TYPE_VERSIONINFO:
      return res_to_bin_versioninfo (wrbfd, off, res->u.versioninfo);
    case RES_TYPE_TOOLBAR:
      return res_to_bin_toolbar (wrbfd, off, res->u.toolbar);
    case RES_TYPE_USERDATA:
    case RES_TYPE_RCDATA:
    default:
      return res_to_bin_rcdata (wrbfd, off, res->u.rcdata);
    }
}