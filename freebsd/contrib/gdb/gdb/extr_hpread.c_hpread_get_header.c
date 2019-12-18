#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct objfile {char* name; int /*<<< orphan*/  obfd; } ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_5__ {int /*<<< orphan*/  version; int /*<<< orphan*/  oi_entries; int /*<<< orphan*/  aa_entries; int /*<<< orphan*/  cd_entries; int /*<<< orphan*/  files; int /*<<< orphan*/  functions; int /*<<< orphan*/  pg_entries; int /*<<< orphan*/  time; int /*<<< orphan*/  globals; int /*<<< orphan*/  inlined; int /*<<< orphan*/  sa_header; int /*<<< orphan*/  bighdr; scalar_t__ pxdbed; int /*<<< orphan*/  md_entries; int /*<<< orphan*/  fd_entries; int /*<<< orphan*/  pd_entries; } ;
typedef  TYPE_1__* PXDB_header_ptr ;
typedef  int /*<<< orphan*/  PXDB_header ;
typedef  TYPE_1__ DOC_info_PXDB_header ;

/* Variables and functions */
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 

__attribute__((used)) static int
hpread_get_header (struct objfile *objfile, PXDB_header_ptr pxdb_header_p)
{
  asection *pinfo_section, *debug_section, *header_section;

#ifdef DUMPING
  /* Turn on for debugging information */
  static int dumping = 0;
#endif

  header_section = bfd_get_section_by_name (objfile->obfd, "$HEADER$");
  if (!header_section)
    {
      /* We don't have either PINFO or DEBUG sections.  But
         stuff like "libc.sl" has no debug info.  There's no
         need to warn the user of this, as it may be ok. The
         caller will figure it out and issue any needed
         messages. */
#ifdef DUMPING
      if (dumping)
	printf ("==No debug info at all for %s.\n", objfile->name);
#endif

      return 0;
    }

  /* We would like either a $DEBUG$ or $PINFO$ section.
     Once we know which, we can understand the header
     data (which we have defined to suit the more common
     $DEBUG$ case). */
  debug_section = bfd_get_section_by_name (objfile->obfd, "$DEBUG$");
  pinfo_section = bfd_get_section_by_name (objfile->obfd, "$PINFO$");
  if (debug_section)
    {
      /* The expected case: normal pxdb header. */
      bfd_get_section_contents (objfile->obfd, header_section,
				pxdb_header_p, 0, sizeof (PXDB_header));

      if (!pxdb_header_p->pxdbed)
	{
	  /* This shouldn't happen if we check in "symfile.c". */
	  return 0;
	}			/* DEBUG section */
    }

  else if (pinfo_section)
    {
      /* The DOC case; we need to translate this into a
         regular header. */
      DOC_info_PXDB_header doc_header;

#ifdef DUMPING
      if (dumping)
	{
	  printf ("==OOps, PINFO, let's try to handle this, %s.\n", objfile->name);
	}
#endif

      bfd_get_section_contents (objfile->obfd,
				header_section,
				&doc_header, 0,
				sizeof (DOC_info_PXDB_header));

      if (!doc_header.pxdbed)
	{
	  /* This shouldn't happen if we check in "symfile.c". */
	  warning ("File \"%s\" not processed by pxdb!", objfile->name);
	  return 0;
	}

      /* Copy relevent fields to standard header passed in. */
      pxdb_header_p->pd_entries = doc_header.pd_entries;
      pxdb_header_p->fd_entries = doc_header.fd_entries;
      pxdb_header_p->md_entries = doc_header.md_entries;
      pxdb_header_p->pxdbed = doc_header.pxdbed;
      pxdb_header_p->bighdr = doc_header.bighdr;
      pxdb_header_p->sa_header = doc_header.sa_header;
      pxdb_header_p->inlined = doc_header.inlined;
      pxdb_header_p->globals = doc_header.globals;
      pxdb_header_p->time = doc_header.time;
      pxdb_header_p->pg_entries = doc_header.pg_entries;
      pxdb_header_p->functions = doc_header.functions;
      pxdb_header_p->files = doc_header.files;
      pxdb_header_p->cd_entries = doc_header.cd_entries;
      pxdb_header_p->aa_entries = doc_header.aa_entries;
      pxdb_header_p->oi_entries = doc_header.oi_entries;
      pxdb_header_p->version = doc_header.version;
    }				/* PINFO section */

  else
    {
#ifdef DUMPING
      if (dumping)
	printf ("==No debug info at all for %s.\n", objfile->name);
#endif

      return 0;

    }

  return 1;
}