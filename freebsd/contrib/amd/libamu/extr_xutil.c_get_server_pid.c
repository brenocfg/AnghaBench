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
 scalar_t__ am_mypid ; 
 scalar_t__ foreground ; 
 scalar_t__ getppid () ; 

long
get_server_pid()
{
  return (long) (foreground ? am_mypid : getppid());
}