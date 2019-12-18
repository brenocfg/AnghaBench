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
 scalar_t__ fwrite (void const*,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static file_ptr
cache_bwrite (struct bfd *abfd, const void *where, file_ptr nbytes)
{
  file_ptr nwrite;
  FILE *f = bfd_cache_lookup (abfd, 0);
  if (f == NULL)
    return 0;
  nwrite = fwrite (where, 1, nbytes, f);
  if (nwrite < nbytes && ferror (f))
    {
      bfd_set_error (bfd_error_system_call);
      return -1;
    }
  return nwrite;
}