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
struct TYPE_3__ {scalar_t__ addr; int /*<<< orphan*/  knconf; } ;
typedef  TYPE_1__ nfs_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (scalar_t__) ; 
 int /*<<< orphan*/  free_knetconfig (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
discard_nfs23_args(nfs_args_t *nap)
{
#ifdef HAVE_TRANSPORT_TYPE_TLI
  free_knetconfig(nap->knconf);
  if (nap->addr)
    XFREE(nap->addr);	/* allocated in compute_nfs_args() */
#endif /* HAVE_TRANSPORT_TYPE_TLI */
}