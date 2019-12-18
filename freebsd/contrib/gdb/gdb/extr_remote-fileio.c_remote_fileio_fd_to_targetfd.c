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
struct TYPE_2__ {int* fd_map; } ;

/* Variables and functions */
 int remote_fileio_next_free_fd () ; 
 TYPE_1__ remote_fio_data ; 

__attribute__((used)) static int
remote_fileio_fd_to_targetfd (int fd)
{
  int target_fd = remote_fileio_next_free_fd ();
  remote_fio_data.fd_map[target_fd] = fd;
  return target_fd;
}