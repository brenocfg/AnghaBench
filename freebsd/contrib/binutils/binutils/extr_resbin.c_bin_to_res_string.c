#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  void* unichar ;
typedef  int rc_uint_type ;
struct TYPE_8__ {TYPE_1__* strings; } ;
typedef  TYPE_3__ rc_stringtable ;
struct TYPE_7__ {TYPE_3__* stringtable; } ;
struct TYPE_9__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ rc_res_resource ;
typedef  int /*<<< orphan*/  bfd_byte ;
struct TYPE_6__ {unsigned int length; void** string; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_STRINGTABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  toosmall (int /*<<< orphan*/ ) ; 
 void* windres_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static rc_res_resource *
bin_to_res_string (windres_bfd *wrbfd, const bfd_byte *data, rc_uint_type length)
{
  rc_stringtable *st;
  int i;
  rc_res_resource *r;

  st = (rc_stringtable *) res_alloc (sizeof (rc_stringtable));

  for (i = 0; i < 16; i++)
    {
      unsigned int slen;

      if (length < 2)
	toosmall (_("stringtable string length"));
      slen = windres_get_16 (wrbfd, data, 2);
      st->strings[i].length = slen;

      if (slen > 0)
	{
	  unichar *s;
	  unsigned int j;

	  if (length < 2 + 2 * slen)
	    toosmall (_("stringtable string"));

	  s = (unichar *) res_alloc (slen * sizeof (unichar));
	  st->strings[i].string = s;

	  for (j = 0; j < slen; j++)
	    s[j] = windres_get_16 (wrbfd, data + 2 + j * 2, 2);
	}

      data += 2 + 2 * slen;
      length -= 2 + 2 * slen;
    }

  r = (rc_res_resource *) res_alloc (sizeof *r);
  r->type = RES_TYPE_STRINGTABLE;
  r->u.stringtable = st;

  return r;
}