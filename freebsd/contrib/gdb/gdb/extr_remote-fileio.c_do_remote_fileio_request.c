#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ui_out {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* func ) (char*) ;scalar_t__ name; } ;

/* Variables and functions */
 int RETURN_ERROR ; 
 int /*<<< orphan*/  remote_fileio_ctrl_c_signal_handler ; 
 int /*<<< orphan*/  remote_fileio_sig_set (int /*<<< orphan*/ ) ; 
 TYPE_1__* remote_fio_func_map ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

__attribute__((used)) static int
do_remote_fileio_request (struct ui_out *uiout, void *buf_arg)
{
  char *buf = buf_arg;
  char *c;
  int idx;

  remote_fileio_sig_set (remote_fileio_ctrl_c_signal_handler);

  c = strchr (++buf, ',');
  if (c)
    *c++ = '\0';
  else
    c = strchr (buf, '\0');
  for (idx = 0; remote_fio_func_map[idx].name; ++idx)
    if (!strcmp (remote_fio_func_map[idx].name, buf))
      break;
  if (!remote_fio_func_map[idx].name)	/* ERROR: No such function. */
    return RETURN_ERROR;
  remote_fio_func_map[idx].func (c);
  return 0;
}