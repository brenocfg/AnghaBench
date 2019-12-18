#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_9__ {scalar_t__ length; scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  w; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  s; } ;
struct TYPE_10__ {int word; TYPE_3__ buffer; TYPE_2__ wstring; TYPE_1__ string; scalar_t__ dword; } ;
struct TYPE_11__ {int type; struct TYPE_11__* next; TYPE_4__ u; } ;
typedef  TYPE_5__ rc_rcdata_item ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  RCDATA_BUFFER 132 
#define  RCDATA_DWORD 131 
#define  RCDATA_STRING 130 
#define  RCDATA_WORD 129 
#define  RCDATA_WSTRING 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  ascii_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  indent (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unicode_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_rc_datablock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
write_rc_rcdata (FILE *e, const rc_rcdata_item *rcdata, int ind)
{
  const rc_rcdata_item *ri;

  indent (e, ind);
  fprintf (e, "BEGIN\n");

  for (ri = rcdata; ri != NULL; ri = ri->next)
    {
      if (ri->type == RCDATA_BUFFER && ri->u.buffer.length == 0)
	continue;

      switch (ri->type)
	{
	default:
	  abort ();

	case RCDATA_WORD:
	  indent (e, ind + 2);
	  fprintf (e, "%ld", (long) (ri->u.word & 0xffff));
	  break;

	case RCDATA_DWORD:
	  indent (e, ind + 2);
	  fprintf (e, "%luL", (unsigned long) ri->u.dword);
	  break;

	case RCDATA_STRING:
	  indent (e, ind + 2);
	  fprintf (e, "\"");
	  ascii_print (e, ri->u.string.s, ri->u.string.length);
	  fprintf (e, "\"");
	  break;

	case RCDATA_WSTRING:
	  indent (e, ind + 2);
	  fprintf (e, "L\"");
	  unicode_print (e, ri->u.wstring.w, ri->u.wstring.length);
	  fprintf (e, "\"");
	  break;

	case RCDATA_BUFFER:
	  write_rc_datablock (e, (rc_uint_type) ri->u.buffer.length,
	  		      (const bfd_byte *) ri->u.buffer.data,
	    		      ri->next != NULL, 0, -1);
	    break;
	}

      if (ri->type != RCDATA_BUFFER)
	{
	  if (ri->next != NULL)
	    fprintf (e, ",");
	  fprintf (e, "\n");
	}
    }

  indent (e, ind);
  fprintf (e, "END\n");
}