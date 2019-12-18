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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NO_OPEN ; 
 int /*<<< orphan*/ * bfd_cache_lookup (struct bfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int fflush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cache_bflush (struct bfd *abfd)
{
  int sts;
  FILE *f = bfd_cache_lookup (abfd, CACHE_NO_OPEN);
  if (f == NULL)
    return 0;
  sts = fflush (f);
  if (sts < 0)
    bfd_set_error (bfd_error_system_call);
  return sts;
}