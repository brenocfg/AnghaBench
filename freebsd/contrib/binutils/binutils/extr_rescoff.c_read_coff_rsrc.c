#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
struct coff_file_info {char const* filename; scalar_t__ secaddr; int /*<<< orphan*/ * data_end; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_res_directory ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_3__ {scalar_t__ ImageBase; } ;
struct TYPE_4__ {TYPE_1__ pe_opthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WR_KIND_BFD ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 int /*<<< orphan*/  bfd_fatal (char const*) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ bfd_get_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_nonfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char const*,char const*) ; 
 int bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  get_windres_bfd_content (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 TYPE_2__* pe_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_coff_res_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct coff_file_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  set_windres_bfd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xexit (int) ; 

rc_res_directory *
read_coff_rsrc (const char *filename, const char *target)
{
  rc_res_directory *ret;
  bfd *abfd;
  windres_bfd wrbfd;
  char **matching;
  asection *sec;
  bfd_size_type size;
  bfd_byte *data;
  struct coff_file_info finfo;

  if (filename == NULL)
    fatal (_("filename required for COFF input"));

  abfd = bfd_openr (filename, target);
  if (abfd == NULL)
    bfd_fatal (filename);

  if (! bfd_check_format_matches (abfd, bfd_object, &matching))
    {
      bfd_nonfatal (bfd_get_filename (abfd));
      if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
	list_matching_formats (matching);
      xexit (1);
    }

  sec = bfd_get_section_by_name (abfd, ".rsrc");
  if (sec == NULL)
    {
      fatal (_("%s: no resource section"), filename);
    }

  set_windres_bfd (&wrbfd, abfd, sec, WR_KIND_BFD);
  size = bfd_section_size (abfd, sec);
  data = (bfd_byte *) res_alloc (size);

  get_windres_bfd_content (&wrbfd, data, 0, size);

  finfo.filename = filename;
  finfo.data = data;
  finfo.data_end = data + size;
  finfo.secaddr = (bfd_get_section_vma (abfd, sec)
		   - pe_data (abfd)->pe_opthdr.ImageBase);

  /* Now just read in the top level resource directory.  Note that we
     don't free data, since we create resource entries that point into
     it.  If we ever want to free up the resource information we read,
     this will have to be cleaned up.  */

  ret = read_coff_res_dir (&wrbfd, data, &finfo, (const rc_res_id *) NULL, 0);
  
  bfd_close (abfd);

  return ret;
}