#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uchar ;
typedef  int cppchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  hash_table; } ;
typedef  TYPE_1__ cpp_reader ;
typedef  int /*<<< orphan*/  cpp_hashnode ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/ * CPP_HASHNODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_ALLOC ; 
 scalar_t__ ISXDIGIT (char const) ; 
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  cpp_errno (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int hex_value (char const) ; 
 int /*<<< orphan*/  ht_lookup (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int one_cppchar_to_utf8 (int,char**,size_t*) ; 

cpp_hashnode *
_cpp_interpret_identifier (cpp_reader *pfile, const uchar *id, size_t len)
{
  /* It turns out that a UCN escape always turns into fewer characters
     than the escape itself, so we can allocate a temporary in advance.  */
  uchar * buf = (uchar *) alloca (len + 1);
  uchar * bufp = buf;
  size_t idp;
  
  for (idp = 0; idp < len; idp++)
    if (id[idp] != '\\')
      *bufp++ = id[idp];
    else
      {
	unsigned length = id[idp+1] == 'u' ? 4 : 8;
	cppchar_t value = 0;
	size_t bufleft = len - (bufp - buf);
	int rval;

	idp += 2;
	while (length && idp < len && ISXDIGIT (id[idp]))
	  {
	    value = (value << 4) + hex_value (id[idp]);
	    idp++;
	    length--;
	  }
	idp--;

	/* Special case for EBCDIC: if the identifier contains
	   a '$' specified using a UCN, translate it to EBCDIC.  */
	if (value == 0x24)
	  {
	    *bufp++ = '$';
	    continue;
	  }

	rval = one_cppchar_to_utf8 (value, &bufp, &bufleft);
	if (rval)
	  {
	    errno = rval;
	    cpp_errno (pfile, CPP_DL_ERROR,
		       "converting UCN to source character set");
	    break;
	  }
      }

  return CPP_HASHNODE (ht_lookup (pfile->hash_table, 
				  buf, bufp - buf, HT_ALLOC));
}