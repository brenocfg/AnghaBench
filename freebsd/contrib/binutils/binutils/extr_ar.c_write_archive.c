#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int has_armap; int /*<<< orphan*/  flags; struct TYPE_11__* archive_next; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_TRADITIONAL_FORMAT ; 
 scalar_t__ ar_truncate ; 
 int /*<<< orphan*/  bfd_archive ; 
 int /*<<< orphan*/  bfd_close (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 int /*<<< orphan*/  bfd_get_filename (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_get_target (TYPE_1__*) ; 
 TYPE_1__* bfd_openw (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_archive_head (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_set_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* make_tempname (char*) ; 
 TYPE_1__* output_bfd ; 
 char* output_filename ; 
 scalar_t__ smart_rename (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ write_armap ; 
 int /*<<< orphan*/  xexit (int) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
write_archive (bfd *iarch)
{
  bfd *obfd;
  char *old_name, *new_name;
  bfd *contents_head = iarch->archive_next;

  old_name = xmalloc (strlen (bfd_get_filename (iarch)) + 1);
  strcpy (old_name, bfd_get_filename (iarch));
  new_name = make_tempname (old_name);

  if (new_name == NULL)
    bfd_fatal ("could not create temporary file whilst writing archive");
  
  output_filename = new_name;

  obfd = bfd_openw (new_name, bfd_get_target (iarch));

  if (obfd == NULL)
    bfd_fatal (old_name);

  output_bfd = obfd;

  bfd_set_format (obfd, bfd_archive);

  /* Request writing the archive symbol table unless we've
     been explicitly requested not to.  */
  obfd->has_armap = write_armap >= 0;

  if (ar_truncate)
    {
      /* This should really use bfd_set_file_flags, but that rejects
         archives.  */
      obfd->flags |= BFD_TRADITIONAL_FORMAT;
    }

  if (!bfd_set_archive_head (obfd, contents_head))
    bfd_fatal (old_name);

  if (!bfd_close (obfd))
    bfd_fatal (old_name);

  output_bfd = NULL;
  output_filename = NULL;

  /* We don't care if this fails; we might be creating the archive.  */
  bfd_close (iarch);

  if (smart_rename (new_name, old_name, 0) != 0)
    xexit (1);
}