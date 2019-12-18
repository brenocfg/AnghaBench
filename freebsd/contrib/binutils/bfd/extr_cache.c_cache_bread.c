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
struct bfd {int dummy; } ;
typedef  scalar_t__ file_ptr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * bfd_cache_lookup (struct bfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fread (void*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,scalar_t__) ; 

__attribute__((used)) static file_ptr
cache_bread (struct bfd *abfd, void *buf, file_ptr nbytes)
{
  FILE *f;
  file_ptr nread;
  /* FIXME - this looks like an optimization, but it's really to cover
     up for a feature of some OSs (not solaris - sigh) that
     ld/pe-dll.c takes advantage of (apparently) when it creates BFDs
     internally and tries to link against them.  BFD seems to be smart
     enough to realize there are no symbol records in the "file" that
     doesn't exist but attempts to read them anyway.  On Solaris,
     attempting to read zero bytes from a NULL file results in a core
     dump, but on other platforms it just returns zero bytes read.
     This makes it to something reasonable. - DJ */
  if (nbytes == 0)
    return 0;

  f = bfd_cache_lookup (abfd, 0);
  if (f == NULL)
    return 0;

#if defined (__VAX) && defined (VMS)
  /* Apparently fread on Vax VMS does not keep the record length
     information.  */
  nread = read (fileno (f), buf, nbytes);
  /* Set bfd_error if we did not read as much data as we expected.  If
     the read failed due to an error set the bfd_error_system_call,
     else set bfd_error_file_truncated.  */
  if (nread == (file_ptr)-1)
    {
      bfd_set_error (bfd_error_system_call);
      return -1;
    }
#else
  nread = fread (buf, 1, nbytes, f);
  /* Set bfd_error if we did not read as much data as we expected.  If
     the read failed due to an error set the bfd_error_system_call,
     else set bfd_error_file_truncated.  */
  if (nread < nbytes && ferror (f))
    {
      bfd_set_error (bfd_error_system_call);
      return -1;
    }
#endif
  return nread;
}