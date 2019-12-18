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
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  int /*<<< orphan*/  unichar ;
typedef  int rc_uint_type ;
struct TYPE_9__ {int length; scalar_t__ data; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/ * w; } ;
struct TYPE_7__ {int length; scalar_t__ s; } ;
struct TYPE_10__ {TYPE_3__ buffer; TYPE_2__ wstring; TYPE_1__ string; int /*<<< orphan*/  dword; int /*<<< orphan*/  word; } ;
struct TYPE_11__ {int type; TYPE_4__ u; struct TYPE_11__* next; } ;
typedef  TYPE_5__ rc_rcdata_item ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
#define  RCDATA_BUFFER 132 
#define  RCDATA_DWORD 131 
#define  RCDATA_STRING 130 
#define  RCDATA_WORD 129 
#define  RCDATA_WSTRING 128 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ reswr_alloc (int) ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rc_uint_type
res_to_bin_rcdata (windres_bfd *wrbfd, rc_uint_type off, const rc_rcdata_item *items)
{
  const rc_rcdata_item *ri;

  for (ri = items; ri != NULL; ri = ri->next)
    {
      rc_uint_type len;
      switch (ri->type)
	{
	default:
	  abort ();
	case RCDATA_WORD:
	  len = 2;
	  break;
	case RCDATA_DWORD:
	  len = 4;
	  break;
	case RCDATA_STRING:
	  len = ri->u.string.length;
	  break;
	case RCDATA_WSTRING:
	  len = ri->u.wstring.length * sizeof (unichar);
	  break;
	case RCDATA_BUFFER:
	  len = ri->u.buffer.length;
	  break;
	}
      if (wrbfd)
	{
	  bfd_byte h[4];
	  bfd_byte *hp = &h[0];
	  switch (ri->type)
	    {
	    case RCDATA_WORD:
	      windres_put_16 (wrbfd, hp, ri->u.word);
	      break;
	    case RCDATA_DWORD:
	      windres_put_32 (wrbfd, hp, ri->u.dword);
	      break;
	    case RCDATA_STRING:
	      hp = (bfd_byte *) ri->u.string.s;
	  break;
	case RCDATA_WSTRING:
	  {
		rc_uint_type i;

		hp = (bfd_byte *) reswr_alloc (len);
	    for (i = 0; i < ri->u.wstring.length; i++)
		  windres_put_16 (wrbfd, hp + i * sizeof (unichar), ri->u.wstring.w[i]);
	  }
	      break;
	case RCDATA_BUFFER:
	      hp = (bfd_byte *) ri->u.buffer.data;
	  break;
	}
	  set_windres_bfd_content (wrbfd, hp, off, len);
    }
      off += len;
    }
  return off;
}