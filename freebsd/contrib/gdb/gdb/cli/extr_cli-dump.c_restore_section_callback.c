#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cleanup {int dummy; } ;
struct callback_data {scalar_t__ load_start; scalar_t__ load_end; scalar_t__ load_offset; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int SEC_LOAD ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  paddr_nz (scalar_t__) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 
 int /*<<< orphan*/  safe_strerror (int) ; 
 int target_write_memory (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
restore_section_callback (bfd *ibfd, asection *isec, void *args)
{
  struct callback_data *data = args;
  bfd_vma sec_start  = bfd_section_vma (ibfd, isec);
  bfd_size_type size = bfd_section_size (ibfd, isec);
  bfd_vma sec_end    = sec_start + size;
  bfd_size_type sec_offset = 0;
  bfd_size_type sec_load_count = size;
  struct cleanup *old_chain;
  char *buf;
  int ret;

  /* Ignore non-loadable sections, eg. from elf files. */
  if (!(bfd_get_section_flags (ibfd, isec) & SEC_LOAD))
    return;

  /* Does the section overlap with the desired restore range? */
  if (sec_end <= data->load_start 
      || (data->load_end > 0 && sec_start >= data->load_end))
    {
      /* No, no useable data in this section. */
      printf_filtered ("skipping section %s...\n", 
		       bfd_section_name (ibfd, isec));
      return;
    }

  /* Compare section address range with user-requested
     address range (if any).  Compute where the actual
     transfer should start and end.  */
  if (sec_start < data->load_start)
    sec_offset = data->load_start - sec_start;
  /* Size of a partial transfer: */
  sec_load_count -= sec_offset;
  if (data->load_end > 0 && sec_end > data->load_end)
    sec_load_count -= sec_end - data->load_end;

  /* Get the data.  */
  buf = xmalloc (size);
  old_chain = make_cleanup (xfree, buf);
  if (!bfd_get_section_contents (ibfd, isec, buf, 0, size))
    error ("Failed to read bfd file %s: '%s'.", bfd_get_filename (ibfd), 
	   bfd_errmsg (bfd_get_error ()));

  printf_filtered ("Restoring section %s (0x%lx to 0x%lx)",
		   bfd_section_name (ibfd, isec), 
		   (unsigned long) sec_start, 
		   (unsigned long) sec_end);

  if (data->load_offset != 0 || data->load_start != 0 || data->load_end != 0)
    printf_filtered (" into memory (0x%s to 0x%s)\n", 
		     paddr_nz ((unsigned long) sec_start 
			       + sec_offset + data->load_offset), 
		     paddr_nz ((unsigned long) sec_start + sec_offset 
		       + data->load_offset + sec_load_count));
  else
    puts_filtered ("\n");

  /* Write the data.  */
  ret = target_write_memory (sec_start + sec_offset + data->load_offset, 
			     buf + sec_offset, sec_load_count);
  if (ret != 0)
    warning ("restore: memory write failed (%s).", safe_strerror (ret));
  do_cleanups (old_chain);
  return;
}