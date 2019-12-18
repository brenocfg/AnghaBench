#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_14__ {char* filename; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_15__ {int flags; char* name; TYPE_2__* section; scalar_t__ value; } ;
typedef  TYPE_4__ asymbol ;
struct TYPE_13__ {scalar_t__ output_offset; TYPE_1__* output_section; } ;
struct TYPE_12__ {scalar_t__ lma; } ;

/* Variables and functions */
 int BSF_DEBUGGING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_bwrite (char*,scalar_t__,TYPE_3__*) ; 
 TYPE_4__** bfd_get_outsymbols (TYPE_3__*) ; 
 int bfd_get_symcount (TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_is_local_label (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sprintf_vma (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static bfd_boolean
srec_write_symbols (bfd *abfd)
{
  /* Dump out the symbols of a bfd.  */
  int i;
  int count = bfd_get_symcount (abfd);

  if (count)
    {
      bfd_size_type len;
      asymbol **table = bfd_get_outsymbols (abfd);

      len = strlen (abfd->filename);
      if (bfd_bwrite ("$$ ", (bfd_size_type) 3, abfd) != 3
	  || bfd_bwrite (abfd->filename, len, abfd) != len
	  || bfd_bwrite ("\r\n", (bfd_size_type) 2, abfd) != 2)
	return FALSE;

      for (i = 0; i < count; i++)
	{
	  asymbol *s = table[i];
	  if (! bfd_is_local_label (abfd, s)
	      && (s->flags & BSF_DEBUGGING) == 0)
	    {
	      /* Just dump out non debug symbols.  */
	      char buf[43], *p;

	      len = strlen (s->name);
	      if (bfd_bwrite ("  ", (bfd_size_type) 2, abfd) != 2
		  || bfd_bwrite (s->name, len, abfd) != len)
		return FALSE;

	      sprintf_vma (buf + 2, (s->value
				     + s->section->output_section->lma
				     + s->section->output_offset));
	      p = buf + 2;
	      while (p[0] == '0' && p[1] != 0)
		p++;
	      len = strlen (p);
	      p[len] = '\r';
	      p[len + 1] = '\n';
	      *--p = '$';
	      *--p = ' ';
	      len += 4;
	      if (bfd_bwrite (p, len, abfd) != len)
		return FALSE;
	    }
	}
      if (bfd_bwrite ("$$ \r\n", (bfd_size_type) 5, abfd) != 5)
	return FALSE;
    }

  return TRUE;
}