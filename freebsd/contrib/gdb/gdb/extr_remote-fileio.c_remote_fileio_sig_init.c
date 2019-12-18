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
struct TYPE_3__ {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  remote_fio_ofunc ; 
 int /*<<< orphan*/  remote_fio_osa ; 
 TYPE_1__ remote_fio_sa ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remote_fileio_sig_init (void)
{
#if defined (HAVE_SIGACTION) && defined (SA_RESTART)
  remote_fio_sa.sa_handler = SIG_IGN;
  sigemptyset (&remote_fio_sa.sa_mask);
  remote_fio_sa.sa_flags = 0;
  sigaction (SIGINT, &remote_fio_sa, &remote_fio_osa);
#else
  remote_fio_ofunc = signal (SIGINT, SIG_IGN);
#endif
}