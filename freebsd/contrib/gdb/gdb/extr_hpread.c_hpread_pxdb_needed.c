#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {int /*<<< orphan*/  obfd; } ;
typedef  int /*<<< orphan*/  PXDB_header ;
typedef  int /*<<< orphan*/  DOC_info_PXDB_header ;

/* Variables and functions */
 char* alloca (int) ; 
 unsigned long bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* objfile ; 

__attribute__((used)) static int
hpread_pxdb_needed (bfd *sym_bfd)
{
  asection *pinfo_section, *debug_section, *header_section;
  unsigned int do_pxdb;
  char *buf;
  bfd_size_type header_section_size;

  unsigned long tmp;
  unsigned int pxdbed;

  header_section = bfd_get_section_by_name (sym_bfd, "$HEADER$");
  if (!header_section)
    {
      return 0;			/* No header at all, can't recover... */
    }

  debug_section = bfd_get_section_by_name (sym_bfd, "$DEBUG$");
  pinfo_section = bfd_get_section_by_name (sym_bfd, "$PINFO$");

  if (pinfo_section && !debug_section)
    {
      /* Debug info with DOC, has different header format. 
         this only happens if the file was pxdbed and compiled optimized
         otherwise the PINFO section is not there. */
      header_section_size = bfd_section_size (objfile->obfd, header_section);

      if (header_section_size == (bfd_size_type) sizeof (DOC_info_PXDB_header))
	{
	  buf = alloca (sizeof (DOC_info_PXDB_header));
	  memset (buf, 0, sizeof (DOC_info_PXDB_header));

	  if (!bfd_get_section_contents (sym_bfd,
					 header_section,
					 buf, 0,
					 header_section_size))
	    error ("bfd_get_section_contents\n");

	  tmp = bfd_get_32 (sym_bfd, (bfd_byte *) (buf + sizeof (int) * 4));
	  pxdbed = (tmp >> 31) & 0x1;

	  if (!pxdbed)
	    error ("file debug header info invalid\n");
	  do_pxdb = 0;
	}

      else
	error ("invalid $HEADER$ size in executable \n");
    }

  else
    {

      /* this can be three different cases:
         1. pxdbed and not doc
         - DEBUG and HEADER sections are there
         - header is PXDB_header type
         - pxdbed flag is set to 1

         2. not pxdbed and doc
         - DEBUG and HEADER  sections are there
         - header is DOC_info_header type
         - pxdbed flag is set to 0

         3. not pxdbed and not doc
         - DEBUG and HEADER sections are there
         - header is XDB_header type
         - pxdbed flag is set to 0

         NOTE: the pxdbed flag is meaningful also in the not
         already pxdb processed version of the header,
         because in case on non-already processed by pxdb files
         that same bit in the header would be always zero.
         Why? Because the bit is the leftmost bit of a word
         which contains a 'length' which is always a positive value
         so that bit is never set to 1 (otherwise it would be negative)

         Given the above, we have two choices : either we ignore the
         size of the header itself and just look at the pxdbed field,
         or we check the size and then we (for safety and paranoia related
         issues) check the bit.
         The first solution is used by DDE, the second by PXDB itself.
         I am using the second one here, because I already wrote it,
         and it is the end of a long day.
         Also, using the first approach would still involve size issues
         because we need to read in the contents of the header section, and
         give the correct amount of stuff we want to read to the
         get_bfd_section_contents function.  */

      /* decide which case depending on the size of the header section.
         The size is as defined in hp-symtab.h  */

      header_section_size = bfd_section_size (objfile->obfd, header_section);

      if (header_section_size == (bfd_size_type) sizeof (PXDB_header))	/* pxdb and not doc */
	{

	  buf = alloca (sizeof (PXDB_header));
	  memset (buf, 0, sizeof (PXDB_header));
	  if (!bfd_get_section_contents (sym_bfd,
					 header_section,
					 buf, 0,
					 header_section_size))
	    error ("bfd_get_section_contents\n");

	  tmp = bfd_get_32 (sym_bfd, (bfd_byte *) (buf + sizeof (int) * 3));
	  pxdbed = (tmp >> 31) & 0x1;

	  if (pxdbed)
	    do_pxdb = 0;
	  else
	    error ("file debug header invalid\n");
	}
      else			/*not pxdbed and doc OR not pxdbed and non doc */
	do_pxdb = 1;
    }

  if (do_pxdb)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}