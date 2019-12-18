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
typedef  int /*<<< orphan*/  unichar ;
typedef  int rc_uint_type ;
struct TYPE_9__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/  w; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/  s; } ;
struct TYPE_10__ {TYPE_3__ buffer; TYPE_2__ wstring; TYPE_1__ string; int /*<<< orphan*/  dword; int /*<<< orphan*/  word; } ;
struct TYPE_11__ {int type; TYPE_4__ u; } ;
typedef  TYPE_5__ rc_rcdata_item ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
#define  RCDATA_BUFFER 132 
#define  RCDATA_DWORD 131 
#define  RCDATA_STRING 130 
#define  RCDATA_WORD 129 
#define  RCDATA_WSTRING 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  windres_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  windres_put_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wrtarget ; 

__attribute__((used)) static rc_uint_type
rcdata_copy (const rc_rcdata_item *src, bfd_byte *dst)
{
  if (! src)
    return 0;
  switch (src->type)
	{
    case RCDATA_WORD:
      if (dst)
	windres_put_16 (&wrtarget, dst, (rc_uint_type) src->u.word);
      return 2;
    case RCDATA_DWORD:
      if (dst)
	windres_put_32 (&wrtarget, dst, (rc_uint_type) src->u.dword);
      return 4;
    case RCDATA_STRING:
      if (dst && src->u.string.length)
	memcpy (dst, src->u.string.s, src->u.string.length);
      return (rc_uint_type) src->u.string.length;
    case RCDATA_WSTRING:
      if (dst && src->u.wstring.length)
	memcpy (dst, src->u.wstring.w, src->u.wstring.length * sizeof (unichar));
      return (rc_uint_type) (src->u.wstring.length  * sizeof (unichar));
    case RCDATA_BUFFER:
      if (dst && src->u.buffer.length)
	memcpy (dst, src->u.buffer.data, src->u.buffer.length);
      return (rc_uint_type) src->u.buffer.length;
    default:
      abort ();
    }
  /* Never reached.  */
  return 0;
}