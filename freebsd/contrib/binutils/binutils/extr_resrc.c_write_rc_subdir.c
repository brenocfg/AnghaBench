#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc_uint_type ;
typedef  int /*<<< orphan*/  rc_res_id ;
struct TYPE_7__ {int /*<<< orphan*/  dir; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_1__ u; int /*<<< orphan*/  named; } ;
struct TYPE_8__ {TYPE_2__ u; TYPE_5__ id; } ;
typedef  TYPE_3__ rc_res_entry ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  RT_ACCELERATOR 148 
#define  RT_ANICURSOR 147 
#define  RT_ANIICON 146 
#define  RT_BITMAP 145 
#define  RT_CURSOR 144 
#define  RT_DIALOG 143 
#define  RT_DLGINCLUDE 142 
#define  RT_FONT 141 
#define  RT_FONTDIR 140 
#define  RT_GROUP_CURSOR 139 
#define  RT_GROUP_ICON 138 
#define  RT_HTML 137 
#define  RT_ICON 136 
#define  RT_MENU 135 
#define  RT_MESSAGETABLE 134 
#define  RT_PLUGPLAY 133 
#define  RT_RCDATA 132 
#define  RT_STRING 131 
#define  RT_TOOLBAR 130 
#define  RT_VERSION 129 
#define  RT_VXD 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  res_id_print (int /*<<< orphan*/ *,TYPE_5__,int) ; 
 int /*<<< orphan*/  wr_printcomment (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  write_rc_directory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
write_rc_subdir (FILE *e, const rc_res_entry *re,
		 const rc_res_id *type, const rc_res_id *name,
		 rc_uint_type *language, int level)
{
  fprintf (e, "\n");
  switch (level)
    {
    case 1:
      wr_printcomment (e, "Type: ");
      if (re->id.named)
	res_id_print (e, re->id, 1);
      else
	{
	  const char *s;

	  switch (re->id.u.id)
	    {
	    case RT_CURSOR: s = "cursor"; break;
	    case RT_BITMAP: s = "bitmap"; break;
	    case RT_ICON: s = "icon"; break;
	    case RT_MENU: s = "menu"; break;
	    case RT_DIALOG: s = "dialog"; break;
	    case RT_STRING: s = "stringtable"; break;
	    case RT_FONTDIR: s = "fontdir"; break;
	    case RT_FONT: s = "font"; break;
	    case RT_ACCELERATOR: s = "accelerators"; break;
	    case RT_RCDATA: s = "rcdata"; break;
	    case RT_MESSAGETABLE: s = "messagetable"; break;
	    case RT_GROUP_CURSOR: s = "group cursor"; break;
	    case RT_GROUP_ICON: s = "group icon"; break;
	    case RT_VERSION: s = "version"; break;
	    case RT_DLGINCLUDE: s = "dlginclude"; break;
	    case RT_PLUGPLAY: s = "plugplay"; break;
	    case RT_VXD: s = "vxd"; break;
	    case RT_ANICURSOR: s = "anicursor"; break;
	    case RT_ANIICON: s = "aniicon"; break;
	    case RT_TOOLBAR: s = "toolbar"; break;
	    case RT_HTML: s = "html"; break;
	    default: s = NULL; break;
	    }

	  if (s != NULL)
	    fprintf (e, "%s", s);
	  else
	    res_id_print (e, re->id, 1);
	}
      break;

    case 2:
      wr_printcomment (e, "Name: ");
      res_id_print (e, re->id, 1);
      break;

    case 3:
      wr_printcomment (e, "Language: ");
      res_id_print (e, re->id, 1);
      break;

    default:
      wr_printcomment (e, "Level %d: ", level);
      res_id_print (e, re->id, 1);
    }

  write_rc_directory (e, re->u.dir, type, name, language, level + 1);
}