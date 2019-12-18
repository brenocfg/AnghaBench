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
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 int remote_fileio_extract_long (char**,scalar_t__*) ; 

__attribute__((used)) static int
remote_fileio_extract_int (char **buf, long *retint)
{
  int ret;
  LONGEST retlong;

  if (!retint)
    return -1;
  ret = remote_fileio_extract_long (buf, &retlong);
  if (!ret)
    *retint = (long) retlong;
  return ret;
}