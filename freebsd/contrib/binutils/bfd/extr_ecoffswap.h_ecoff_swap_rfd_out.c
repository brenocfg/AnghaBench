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
struct rfd_ext {int /*<<< orphan*/  rfd; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  RFDT ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void
ecoff_swap_rfd_out (bfd *abfd, const RFDT *intern, void * ext_ptr)
{
  struct rfd_ext *ext = (struct rfd_ext *) ext_ptr;

  H_PUT_32 (abfd, *intern, ext->rfd);

#ifdef TEST
  if (memcmp ((char *) ext, (char *) intern, sizeof (*intern)) != 0)
    abort ();
#endif
}