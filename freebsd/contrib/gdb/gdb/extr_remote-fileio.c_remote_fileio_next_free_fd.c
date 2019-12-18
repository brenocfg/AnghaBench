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
struct TYPE_2__ {int fd_map_size; scalar_t__* fd_map; } ;

/* Variables and functions */
 scalar_t__ FIO_FD_INVALID ; 
 int remote_fileio_resize_fd_map () ; 
 TYPE_1__ remote_fio_data ; 

__attribute__((used)) static int
remote_fileio_next_free_fd (void)
{
  int i;

  for (i = 0; i < remote_fio_data.fd_map_size; ++i)
    if (remote_fio_data.fd_map[i] == FIO_FD_INVALID)
      return i;
  return remote_fileio_resize_fd_map ();
}