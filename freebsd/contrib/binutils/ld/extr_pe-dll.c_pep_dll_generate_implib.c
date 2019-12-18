#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int num_exports; TYPE_9__* exports; scalar_t__ name; } ;
typedef  TYPE_2__ def_file ;
struct TYPE_20__ {int has_armap; struct TYPE_20__* archive_next; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_22__ {char* internal_name; char* name; int /*<<< orphan*/  flag_data; } ;
struct TYPE_21__ {TYPE_1__* exports; } ;
struct TYPE_18__ {scalar_t__ flag_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISALNUM (char) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_archive ; 
 int /*<<< orphan*/  bfd_close (TYPE_3__*) ; 
 TYPE_3__* bfd_openw (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_archive_head (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_set_format (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dll_filename ; 
 scalar_t__ dll_name ; 
 char* dll_symname ; 
 int /*<<< orphan*/  einfo (char*,...) ; 
 int /*<<< orphan*/  info_msg (char*,char const*) ; 
 TYPE_3__* make_head (TYPE_3__*) ; 
 TYPE_3__* make_one (TYPE_9__*,TYPE_3__*,int) ; 
 TYPE_3__* make_tail (TYPE_3__*) ; 
 TYPE_5__* pe_def_file ; 
 int /*<<< orphan*/  unlink_if_ordinary (char const*) ; 
 char* xstrdup (scalar_t__) ; 

void
pe_dll_generate_implib (def_file *def, const char *impfilename)
{
  int i;
  bfd *ar_head;
  bfd *ar_tail;
  bfd *outarch;
  bfd *head = 0;

  dll_filename = (def->name) ? def->name : dll_name;
  dll_symname = xstrdup (dll_filename);
  for (i = 0; dll_symname[i]; i++)
    if (!ISALNUM (dll_symname[i]))
      dll_symname[i] = '_';

  unlink_if_ordinary (impfilename);

  outarch = bfd_openw (impfilename, 0);

  if (!outarch)
    {
      /* xgettext:c-format */
      einfo (_("%XCan't open .lib file: %s\n"), impfilename);
      return;
    }

  /* xgettext:c-format */
  info_msg (_("Creating library file: %s\n"), impfilename);
 
  bfd_set_format (outarch, bfd_archive);
  outarch->has_armap = 1;

  /* Work out a reasonable size of things to put onto one line.  */
  ar_head = make_head (outarch);

  for (i = 0; i < def->num_exports; i++)
    {
      /* The import library doesn't know about the internal name.  */
      char *internal = def->exports[i].internal_name;
      bfd *n;

      /* Don't add PRIVATE entries to import lib.  */ 	
      if (pe_def_file->exports[i].flag_private)
	continue;
      def->exports[i].internal_name = def->exports[i].name;
      n = make_one (def->exports + i, outarch,
		    ! (def->exports + i)->flag_data);
      n->archive_next = head;
      head = n;
      def->exports[i].internal_name = internal;
    }

  ar_tail = make_tail (outarch);

  if (ar_head == NULL || ar_tail == NULL)
    return;

  /* Now stick them all into the archive.  */
  ar_head->archive_next = head;
  ar_tail->archive_next = ar_head;
  head = ar_tail;

  if (! bfd_set_archive_head (outarch, head))
    einfo ("%Xbfd_set_archive_head: %E\n");

  if (! bfd_close (outarch))
    einfo ("%Xbfd_close %s: %E\n", impfilename);

  while (head != NULL)
    {
      bfd *n = head->archive_next;
      bfd_close (head);
      head = n;
    }
}