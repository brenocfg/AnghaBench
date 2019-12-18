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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int remote_write_bytes (int,char*,int) ; 

__attribute__((used)) static int
remote_fileio_write_bytes (CORE_ADDR memaddr, char *myaddr, int len)
{
  int ret = 0, written;

  while (len > 0 && (written = remote_write_bytes (memaddr, myaddr, len)) > 0)
    {
      len -= written;
      memaddr += written;
      myaddr += written;
      ret += written;
    }
  return ret;
}