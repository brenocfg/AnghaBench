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
typedef  int /*<<< orphan*/  host_callback ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_stdtarg ; 
 int /*<<< orphan*/  ui_file_write (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
gdb_os_write_stdout (host_callback *p, const char *buf, int len)
{
  int i;
  char b[2];

  ui_file_write (gdb_stdtarg, buf, len);
  return len;
}