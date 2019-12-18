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

/* Variables and functions */
 int /*<<< orphan*/  RETURN_QUIT ; 
 void SIG_IGN (int) ; 
 int /*<<< orphan*/  remote_fileio_sig_set (void (*) (int)) ; 
 int remote_fio_ctrl_c_flag ; 
 int /*<<< orphan*/  remote_fio_no_longjmp ; 
 int /*<<< orphan*/  throw_exception (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remote_fileio_ctrl_c_signal_handler (int signo)
{
  remote_fileio_sig_set (SIG_IGN);
  remote_fio_ctrl_c_flag = 1;
  if (!remote_fio_no_longjmp)
    throw_exception (RETURN_QUIT);
  remote_fileio_sig_set (remote_fileio_ctrl_c_signal_handler);
}