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
struct TYPE_2__ {int fd_map_size; int /*<<< orphan*/ * fd_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIO_FD_INVALID ; 
 int /*<<< orphan*/  remote_fileio_init_fd_map () ; 
 TYPE_1__ remote_fio_data ; 

__attribute__((used)) static void
remote_fileio_close_target_fd (int target_fd)
{
  remote_fileio_init_fd_map ();
  if (target_fd >= 0 && target_fd < remote_fio_data.fd_map_size)
    remote_fio_data.fd_map[target_fd] = FIO_FD_INVALID;
}