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
struct TYPE_13__ {TYPE_7__* var; TYPE_8__* fixed; } ;
typedef  TYPE_4__ rc_versioninfo ;
struct TYPE_14__ {scalar_t__ charset; scalar_t__ language; struct TYPE_14__* next; } ;
typedef  TYPE_5__ rc_ver_varinfo ;
struct TYPE_15__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; struct TYPE_15__* next; } ;
typedef  TYPE_6__ rc_ver_stringinfo ;
struct TYPE_11__ {TYPE_5__* var; int /*<<< orphan*/  key; } ;
struct TYPE_10__ {TYPE_6__* strings; int /*<<< orphan*/  language; } ;
struct TYPE_12__ {TYPE_2__ var; TYPE_1__ string; } ;
struct TYPE_16__ {int type; TYPE_3__ u; struct TYPE_16__* next; } ;
typedef  TYPE_7__ rc_ver_info ;
struct TYPE_17__ {int file_version_ms; int file_version_ls; int product_version_ms; int product_version_ls; scalar_t__ file_flags_mask; scalar_t__ file_flags; scalar_t__ file_os; scalar_t__ file_type; scalar_t__ file_subtype; scalar_t__ file_date_ms; scalar_t__ file_date_ls; } ;
typedef  TYPE_8__ rc_fixed_versioninfo ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  VERINFO_STRING 129 
#define  VERINFO_VAR 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  unicode_print_quoted (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
write_rc_versioninfo (FILE *e, const rc_versioninfo *versioninfo)
{
  const rc_fixed_versioninfo *f;
  const rc_ver_info *vi;

  f = versioninfo->fixed;
  if (f->file_version_ms != 0 || f->file_version_ls != 0)
    fprintf (e, " FILEVERSION %u, %u, %u, %u\n",
	     (unsigned int) ((f->file_version_ms >> 16) & 0xffff),
	     (unsigned int) (f->file_version_ms & 0xffff),
	     (unsigned int) ((f->file_version_ls >> 16) & 0xffff),
	     (unsigned int) (f->file_version_ls & 0xffff));
  if (f->product_version_ms != 0 || f->product_version_ls != 0)
    fprintf (e, " PRODUCTVERSION %u, %u, %u, %u\n",
	     (unsigned int) ((f->product_version_ms >> 16) & 0xffff),
	     (unsigned int) (f->product_version_ms & 0xffff),
	     (unsigned int) ((f->product_version_ls >> 16) & 0xffff),
	     (unsigned int) (f->product_version_ls & 0xffff));
  if (f->file_flags_mask != 0)
    fprintf (e, " FILEFLAGSMASK 0x%x\n", (unsigned int) f->file_flags_mask);
  if (f->file_flags != 0)
    fprintf (e, " FILEFLAGS 0x%x\n", (unsigned int) f->file_flags);
  if (f->file_os != 0)
    fprintf (e, " FILEOS 0x%x\n", (unsigned int) f->file_os);
  if (f->file_type != 0)
    fprintf (e, " FILETYPE 0x%x\n", (unsigned int) f->file_type);
  if (f->file_subtype != 0)
    fprintf (e, " FILESUBTYPE 0x%x\n", (unsigned int) f->file_subtype);
  if (f->file_date_ms != 0 || f->file_date_ls != 0)
    fprintf (e, "/* Date: %u, %u.  */\n",
    	     (unsigned int) f->file_date_ms, (unsigned int) f->file_date_ls);

  fprintf (e, "BEGIN\n");

  for (vi = versioninfo->var; vi != NULL; vi = vi->next)
    {
      switch (vi->type)
	{
	case VERINFO_STRING:
	  {
	    const rc_ver_stringinfo *vs;

	    fprintf (e, "  BLOCK \"StringFileInfo\"\n");
	    fprintf (e, "  BEGIN\n");
	    fprintf (e, "    BLOCK ");
	    unicode_print_quoted (e, vi->u.string.language, -1);
	    fprintf (e, "\n");
	    fprintf (e, "    BEGIN\n");

	    for (vs = vi->u.string.strings; vs != NULL; vs = vs->next)
	      {
		fprintf (e, "      VALUE ");
		unicode_print_quoted (e, vs->key, -1);
		fprintf (e, ", ");
		unicode_print_quoted (e, vs->value, -1);
		fprintf (e, "\n");
	      }

	    fprintf (e, "    END\n");
	    fprintf (e, "  END\n");
	    break;
	  }

	case VERINFO_VAR:
	  {
	    const rc_ver_varinfo *vv;

	    fprintf (e, "  BLOCK \"VarFileInfo\"\n");
	    fprintf (e, "  BEGIN\n");
	    fprintf (e, "    VALUE ");
	    unicode_print_quoted (e, vi->u.var.key, -1);

	    for (vv = vi->u.var.var; vv != NULL; vv = vv->next)
	      fprintf (e, ", 0x%x, %d", (unsigned int) vv->language,
		       (int) vv->charset);

	    fprintf (e, "\n  END\n");

	    break;
	  }
	}
    }

  fprintf (e, "END\n");
}