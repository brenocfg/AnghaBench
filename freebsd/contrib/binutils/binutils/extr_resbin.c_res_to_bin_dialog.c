#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
struct bin_dialogfont {struct bin_dialogfont* off; struct bin_dialogfont* id; struct bin_dialogfont* height; struct bin_dialogfont* width; struct bin_dialogfont* y; struct bin_dialogfont* x; struct bin_dialogfont* style; struct bin_dialogfont* exstyle; struct bin_dialogfont* help; int /*<<< orphan*/  charset; int /*<<< orphan*/  italic; struct bin_dialogfont* weight; struct bin_dialogfont* pointsize; struct bin_dialogfont* sig2; struct bin_dialogfont* sig1; } ;
struct bin_dialogexfont {struct bin_dialogexfont* off; struct bin_dialogexfont* id; struct bin_dialogexfont* height; struct bin_dialogexfont* width; struct bin_dialogexfont* y; struct bin_dialogexfont* x; struct bin_dialogexfont* style; struct bin_dialogexfont* exstyle; struct bin_dialogexfont* help; int /*<<< orphan*/  charset; int /*<<< orphan*/  italic; struct bin_dialogexfont* weight; struct bin_dialogexfont* pointsize; struct bin_dialogexfont* sig2; struct bin_dialogexfont* sig1; } ;
struct bin_dialogex_control {struct bin_dialogex_control* off; struct bin_dialogex_control* id; struct bin_dialogex_control* height; struct bin_dialogex_control* width; struct bin_dialogex_control* y; struct bin_dialogex_control* x; struct bin_dialogex_control* style; struct bin_dialogex_control* exstyle; struct bin_dialogex_control* help; int /*<<< orphan*/  charset; int /*<<< orphan*/  italic; struct bin_dialogex_control* weight; struct bin_dialogex_control* pointsize; struct bin_dialogex_control* sig2; struct bin_dialogex_control* sig1; } ;
struct bin_dialogex {struct bin_dialogex* off; struct bin_dialogex* id; struct bin_dialogex* height; struct bin_dialogex* width; struct bin_dialogex* y; struct bin_dialogex* x; struct bin_dialogex* style; struct bin_dialogex* exstyle; struct bin_dialogex* help; int /*<<< orphan*/  charset; int /*<<< orphan*/  italic; struct bin_dialogex* weight; struct bin_dialogex* pointsize; struct bin_dialogex* sig2; struct bin_dialogex* sig1; } ;
struct bin_dialog_control {struct bin_dialog_control* off; struct bin_dialog_control* id; struct bin_dialog_control* height; struct bin_dialog_control* width; struct bin_dialog_control* y; struct bin_dialog_control* x; struct bin_dialog_control* style; struct bin_dialog_control* exstyle; struct bin_dialog_control* help; int /*<<< orphan*/  charset; int /*<<< orphan*/  italic; struct bin_dialog_control* weight; struct bin_dialog_control* pointsize; struct bin_dialog_control* sig2; struct bin_dialog_control* sig1; } ;
struct bin_dialog {struct bin_dialog* off; struct bin_dialog* id; struct bin_dialog* height; struct bin_dialog* width; struct bin_dialog* y; struct bin_dialog* x; struct bin_dialog* style; struct bin_dialog* exstyle; struct bin_dialog* help; int /*<<< orphan*/  charset; int /*<<< orphan*/  italic; struct bin_dialog* weight; struct bin_dialog* pointsize; struct bin_dialog* sig2; struct bin_dialog* sig1; } ;
typedef  int rc_uint_type ;
struct TYPE_7__ {int style; int exstyle; int x; int y; int width; int height; int id; int help; int /*<<< orphan*/ * data; int /*<<< orphan*/  text; int /*<<< orphan*/  class; struct TYPE_7__* next; } ;
typedef  TYPE_2__ rc_dialog_control ;
struct TYPE_8__ {int style; int exstyle; int x; int y; int width; int height; int pointsize; TYPE_2__* controls; int /*<<< orphan*/  font; TYPE_1__* ex; int /*<<< orphan*/  caption; int /*<<< orphan*/  class; int /*<<< orphan*/  menu; } ;
typedef  TYPE_3__ rc_dialog ;
typedef  struct bin_dialogfont bfd_byte ;
struct TYPE_6__ {int help; int weight; int italic; int charset; } ;

/* Variables and functions */
 int BIN_DIALOGEXFONT_SIZE ; 
 int BIN_DIALOGEX_CONTROL_SIZE ; 
 int BIN_DIALOGEX_SIZE ; 
 int BIN_DIALOGFONT_SIZE ; 
 int BIN_DIALOG_CONTROL_SIZE ; 
 int BIN_DIALOG_SIZE ; 
 int DS_SETFONT ; 
 int extended_dialog (TYPE_3__ const*) ; 
 int res_to_bin_rcdata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int resid_to_bin (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,struct bin_dialogfont*,int,int) ; 
 int unicode_to_bin (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,struct bin_dialogfont*,int) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,struct bin_dialogfont*,int) ; 
 int /*<<< orphan*/  windres_put_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_dialog (windres_bfd *wrbfd, rc_uint_type off, const rc_dialog *dialog)
{
  rc_uint_type off_delta;
  rc_uint_type start, marker;
  int dialogex;
  int c;
  rc_dialog_control *dc;
  struct bin_dialogex bdx;
  struct bin_dialog bd;

  off_delta = off;
  start = off;
  dialogex = extended_dialog (dialog);

  if (wrbfd)
    {
  if (! dialogex)
    {
	  windres_put_32 (wrbfd, bd.style, dialog->style);
	  windres_put_32 (wrbfd, bd.exstyle, dialog->exstyle);
	  windres_put_16 (wrbfd, bd.x, dialog->x);
	  windres_put_16 (wrbfd, bd.y, dialog->y);
	  windres_put_16 (wrbfd, bd.width, dialog->width);
	  windres_put_16 (wrbfd, bd.height, dialog->height);
    }
  else
    {
	  windres_put_16 (wrbfd, bdx.sig1, 1);
	  windres_put_16 (wrbfd, bdx.sig2, 0xffff);
	  windres_put_32 (wrbfd, bdx.help, (dialog->ex ? dialog->ex->help : 0));
	  windres_put_32 (wrbfd, bdx.exstyle, dialog->exstyle);
	  windres_put_32 (wrbfd, bdx.style, dialog->style);
	  windres_put_16 (wrbfd, bdx.x, dialog->x);
	  windres_put_16 (wrbfd, bdx.y, dialog->y);
	  windres_put_16 (wrbfd, bdx.width, dialog->width);
	  windres_put_16 (wrbfd, bdx.height, dialog->height);
	}
    }

  off += (dialogex != 0 ? BIN_DIALOGEX_SIZE : BIN_DIALOG_SIZE);

  off = resid_to_bin (wrbfd, off, dialog->menu);
  off = resid_to_bin (wrbfd, off, dialog->class);
  off = unicode_to_bin (wrbfd, off, dialog->caption);

  if ((dialog->style & DS_SETFONT) != 0)
    {
      if (wrbfd)
	{
	  if (! dialogex)
	    {
	      struct bin_dialogfont bdf;
	      windres_put_16 (wrbfd, bdf.pointsize, dialog->pointsize);
	      set_windres_bfd_content (wrbfd, &bdf, off, BIN_DIALOGFONT_SIZE);
	    }
	  else
	    {
	      struct bin_dialogexfont bdxf;
	      windres_put_16 (wrbfd, bdxf.pointsize, dialog->pointsize);
	      windres_put_16 (wrbfd, bdxf.weight, (dialog->ex == NULL ? 0 : dialog->ex->weight));
	      windres_put_8 (wrbfd, bdxf.italic, (dialog->ex == NULL ? 0 : dialog->ex->italic));
	      windres_put_8 (wrbfd, bdxf.charset, (dialog->ex == NULL ? 1 : dialog->ex->charset));
	      set_windres_bfd_content (wrbfd, &bdxf, off, BIN_DIALOGEXFONT_SIZE);
	    }
	}
      off += (dialogex ? BIN_DIALOGEXFONT_SIZE : BIN_DIALOGFONT_SIZE);
      off = unicode_to_bin (wrbfd, off, dialog->font);
    }
  for (c = 0, dc = dialog->controls; dc != NULL; dc = dc->next, c++)
    {
      bfd_byte dc_rclen[2];

      off += (4 - ((off - off_delta) & 3)) & 3;
      if (wrbfd)
	{
      if (! dialogex)
	{
	      struct bin_dialog_control bdc;

	      windres_put_32 (wrbfd, bdc.style, dc->style);
	      windres_put_32 (wrbfd, bdc.exstyle, dc->exstyle);
	      windres_put_16 (wrbfd, bdc.x, dc->x);
	      windres_put_16 (wrbfd, bdc.y, dc->y);
	      windres_put_16 (wrbfd, bdc.width, dc->width);
	      windres_put_16 (wrbfd, bdc.height, dc->height);
	      windres_put_16 (wrbfd, bdc.id, dc->id);
	      set_windres_bfd_content (wrbfd, &bdc, off, BIN_DIALOG_CONTROL_SIZE);
	}
      else
	{
	      struct bin_dialogex_control bdc;

	      windres_put_32 (wrbfd, bdc.help, dc->help);
	      windres_put_32 (wrbfd, bdc.exstyle, dc->exstyle);
	      windres_put_32 (wrbfd, bdc.style, dc->style);
	      windres_put_16 (wrbfd, bdc.x, dc->x);
	      windres_put_16 (wrbfd, bdc.y, dc->y);
	      windres_put_16 (wrbfd, bdc.width, dc->width);
	      windres_put_16 (wrbfd, bdc.height, dc->height);
	      windres_put_32 (wrbfd, bdc.id, dc->id);
	      set_windres_bfd_content (wrbfd, &bdc, off, BIN_DIALOGEX_CONTROL_SIZE);
	    }
	}      
      off += (dialogex != 0 ? BIN_DIALOGEX_CONTROL_SIZE : BIN_DIALOG_CONTROL_SIZE);

      off = resid_to_bin (wrbfd, off, dc->class);
      off = resid_to_bin (wrbfd, off, dc->text);

      marker = off; /* Save two bytes for size of optional data.  */
      off += 2;

      if (dc->data == NULL)
        {
	  if (wrbfd)
	    windres_put_16 (wrbfd, dc_rclen, 0);
	}
      else
	{
	  rc_uint_type saved_off = off;
	  rc_uint_type old_off;
	  off += (4 - ((off - off_delta) & 3)) & 3;

	  old_off = off;
	  off = res_to_bin_rcdata (wrbfd, off, dc->data);
	  if ((off - old_off) == 0)
	    old_off = off = saved_off;
	  if (wrbfd)
	    windres_put_16 (wrbfd, dc_rclen, off - old_off);
	    }
      if (wrbfd)
	set_windres_bfd_content (wrbfd, dc_rclen, marker, 2);
	}

  if (wrbfd)
    {
      windres_put_16 (wrbfd, (dialogex != 0 ? bdx.off : bd.off), c);
      if (! dialogex)
	set_windres_bfd_content (wrbfd, &bd, start, BIN_DIALOG_SIZE);
      else
	set_windres_bfd_content (wrbfd, &bdx, start, BIN_DIALOGEX_SIZE);
    }

  return off;
}