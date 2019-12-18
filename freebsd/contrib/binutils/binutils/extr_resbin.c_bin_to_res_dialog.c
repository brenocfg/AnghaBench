#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  int rc_uint_type ;
struct TYPE_12__ {TYPE_8__* dialog; } ;
struct TYPE_13__ {TYPE_3__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ rc_res_resource ;
struct TYPE_10__ {int length; int /*<<< orphan*/  const* data; } ;
struct TYPE_11__ {TYPE_1__ buffer; } ;
struct TYPE_14__ {TYPE_2__ u; int /*<<< orphan*/  type; int /*<<< orphan*/ * next; } ;
typedef  TYPE_5__ rc_rcdata_item ;
struct TYPE_15__ {int charset; void* italic; void* weight; void* help; } ;
typedef  TYPE_6__ rc_dialog_ex ;
struct TYPE_16__ {struct TYPE_16__* next; TYPE_5__* data; int /*<<< orphan*/  text; int /*<<< orphan*/  class; void* id; void* height; void* width; void* y; void* x; void* style; void* exstyle; void* help; } ;
typedef  TYPE_7__ rc_dialog_control ;
struct TYPE_17__ {int style; TYPE_6__* ex; TYPE_7__* controls; int /*<<< orphan*/ * font; void* pointsize; int /*<<< orphan*/ * caption; int /*<<< orphan*/  class; int /*<<< orphan*/  menu; void* height; void* width; void* y; void* x; void* exstyle; } ;
typedef  TYPE_8__ rc_dialog ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int DS_SETFONT ; 
 int /*<<< orphan*/  RCDATA_BUFFER ; 
 int /*<<< orphan*/  RES_TYPE_DIALOG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,int) ; 
 int get_resid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 void* get_unicode (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int*) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  toosmall (int /*<<< orphan*/ ) ; 
 void* windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 void* windres_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 void* windres_get_8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static rc_res_resource *
bin_to_res_dialog (windres_bfd *wrbfd, const bfd_byte *data, rc_uint_type length)
{
  rc_uint_type signature;
  rc_dialog *d;
  rc_uint_type c, sublen, i;
  rc_uint_type off;
  rc_dialog_control **pp;
  rc_res_resource *r;

  if (length < 18)
    toosmall (_("dialog header"));

  d = (rc_dialog *) res_alloc (sizeof (rc_dialog));

  signature = windres_get_16 (wrbfd, data + 2, 2);
  if (signature != 0xffff)
    {
      d->ex = NULL;
      d->style = windres_get_32 (wrbfd, data, 4);
      d->exstyle = windres_get_32 (wrbfd, data + 4, 4);
      off = 8;
    }
  else
    {
      int version;

      version = windres_get_16 (wrbfd, data, 2);
      if (version != 1)
	fatal (_("unexpected DIALOGEX version %d"), version);

      d->ex = (rc_dialog_ex *) res_alloc (sizeof (rc_dialog_ex));
      d->ex->help = windres_get_32 (wrbfd, data + 4, 4);
      d->exstyle = windres_get_32 (wrbfd, data + 8, 4);
      d->style = windres_get_32 (wrbfd, data + 12, 4);
      off = 16;
    }

  if (length < off + 10)
    toosmall (_("dialog header"));

  c = windres_get_16 (wrbfd, data + off, 2);
  d->x = windres_get_16 (wrbfd, data + off + 2, 2);
  d->y = windres_get_16 (wrbfd, data + off + 4, 2);
  d->width = windres_get_16 (wrbfd, data + off + 6, 2);
  d->height = windres_get_16 (wrbfd, data + off + 8, 2);

  off += 10;

  sublen = get_resid (wrbfd, &d->menu, data + off, length - off);
  off += sublen;

  sublen = get_resid (wrbfd, &d->class, data + off, length - off);
  off += sublen;

  d->caption = get_unicode (wrbfd, data + off, length - off, &sublen);
  off += sublen * 2 + 2;
  if (sublen == 0)
    d->caption = NULL;

  if ((d->style & DS_SETFONT) == 0)
    {
      d->pointsize = 0;
      d->font = NULL;
      if (d->ex != NULL)
	{
	  d->ex->weight = 0;
	  d->ex->italic = 0;
	  d->ex->charset = 1; /* Default charset.  */
	}
    }
  else
    {
      if (length < off + 2)
	toosmall (_("dialog font point size"));

      d->pointsize = windres_get_16 (wrbfd, data + off, 2);
      off += 2;

      if (d->ex != NULL)
	{
	  if (length < off + 4)
	    toosmall (_("dialogex font information"));
	  d->ex->weight = windres_get_16 (wrbfd, data + off, 2);
	  d->ex->italic = windres_get_8 (wrbfd, data + off + 2, 1);
	  d->ex->charset = windres_get_8 (wrbfd, data + off + 3, 1);
	  off += 4;
	}

      d->font = get_unicode (wrbfd, data + off, length - off, &sublen);
      off += sublen * 2 + 2;
    }

  d->controls = NULL;
  pp = &d->controls;

  for (i = 0; i < c; i++)
    {
      rc_dialog_control *dc;
      int datalen;

      off = (off + 3) &~ 3;

      dc = (rc_dialog_control *) res_alloc (sizeof (rc_dialog_control));

      if (d->ex == NULL)
	{
	  if (length < off + 8)
	    toosmall (_("dialog control"));

	  dc->style = windres_get_32 (wrbfd, data + off, 4);
	  dc->exstyle = windres_get_32 (wrbfd, data + off + 4, 4);
	  dc->help = 0;
	  off += 8;
	}
      else
	{
	  if (length < off + 12)
	    toosmall (_("dialogex control"));
	  dc->help = windres_get_32 (wrbfd, data + off, 4);
	  dc->exstyle = windres_get_32 (wrbfd, data + off + 4, 4);
	  dc->style = windres_get_32 (wrbfd, data + off + 8, 4);
	  off += 12;
	}

      if (length < off + (d->ex != NULL ? 2 : 0) + 10)
	toosmall (_("dialog control"));

      dc->x = windres_get_16 (wrbfd, data + off, 2);
      dc->y = windres_get_16 (wrbfd, data + off + 2, 2);
      dc->width = windres_get_16 (wrbfd, data + off + 4, 2);
      dc->height = windres_get_16 (wrbfd, data + off + 6, 2);

      if (d->ex != NULL)
	dc->id = windres_get_32 (wrbfd, data + off + 8, 4);
      else
	dc->id = windres_get_16 (wrbfd, data + off + 8, 2);

      off += 10 + (d->ex != NULL ? 2 : 0);

      sublen = get_resid (wrbfd, &dc->class, data + off, length - off);
      off += sublen;

      sublen = get_resid (wrbfd, &dc->text, data + off, length - off);
      off += sublen;

      if (length < off + 2)
	toosmall (_("dialog control end"));

      datalen = windres_get_16 (wrbfd, data + off, 2);
      off += 2;

      if (datalen == 0)
	dc->data = NULL;
      else
	{
	  off = (off + 3) &~ 3;

	  if (length < off + datalen)
	    toosmall (_("dialog control data"));

	  dc->data = ((rc_rcdata_item *)
		      res_alloc (sizeof (rc_rcdata_item)));
	  dc->data->next = NULL;
	  dc->data->type = RCDATA_BUFFER;
	  dc->data->u.buffer.length = datalen;
	  dc->data->u.buffer.data = data + off;

	  off += datalen;
	}

      dc->next = NULL;
      *pp = dc;
      pp = &dc->next;
    }

  r = (rc_res_resource *) res_alloc (sizeof *r);
  r->type = RES_TYPE_DIALOG;
  r->u.dialog = d;

  return r;
}