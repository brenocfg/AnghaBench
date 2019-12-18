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
struct TYPE_3__ {void (* sa_handler ) (int) ;scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 TYPE_1__ remote_fio_sa ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 

__attribute__((used)) static void
remote_fileio_sig_set (void (*sigint_func)(int))
{
#if defined (HAVE_SIGACTION) && defined (SA_RESTART)
  remote_fio_sa.sa_handler = sigint_func;
  sigemptyset (&remote_fio_sa.sa_mask);
  remote_fio_sa.sa_flags = 0;
  sigaction (SIGINT, &remote_fio_sa, NULL);
#else
  signal (SIGINT, sigint_func);
#endif
}