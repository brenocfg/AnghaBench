#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dnr_ext {int /*<<< orphan*/  d_index; int /*<<< orphan*/  d_rfd; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int /*<<< orphan*/  index; int /*<<< orphan*/  rfd; } ;
typedef  TYPE_1__ DNR ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void
ecoff_swap_dnr_out (bfd *abfd, const DNR *intern_copy, void * ext_ptr)
{
  struct dnr_ext *ext = (struct dnr_ext *) ext_ptr;
  DNR intern[1];

  /* Make it reasonable to do in-place.  */
  *intern = *intern_copy;

  H_PUT_32 (abfd, intern->rfd, ext->d_rfd);
  H_PUT_32 (abfd, intern->index, ext->d_index);

#ifdef TEST
  if (memcmp ((char *) ext, (char *) intern, sizeof (*intern)) != 0)
    abort ();
#endif
}