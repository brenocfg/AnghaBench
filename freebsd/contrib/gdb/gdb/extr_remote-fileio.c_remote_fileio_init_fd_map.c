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
struct TYPE_2__ {int* fd_map; int fd_map_size; } ;

/* Variables and functions */
 int FIO_FD_CONSOLE_IN ; 
 void* FIO_FD_CONSOLE_OUT ; 
 int FIO_FD_INVALID ; 
 TYPE_1__ remote_fio_data ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static int
remote_fileio_init_fd_map (void)
{
  int i;

  if (!remote_fio_data.fd_map)
    {
      remote_fio_data.fd_map = (int *) xmalloc (10 * sizeof (int));
      remote_fio_data.fd_map_size = 10;
      remote_fio_data.fd_map[0] = FIO_FD_CONSOLE_IN;
      remote_fio_data.fd_map[1] = FIO_FD_CONSOLE_OUT;
      remote_fio_data.fd_map[2] = FIO_FD_CONSOLE_OUT;
      for (i = 3; i < 10; ++i)
        remote_fio_data.fd_map[i] = FIO_FD_INVALID;
    }
  return 3;
}