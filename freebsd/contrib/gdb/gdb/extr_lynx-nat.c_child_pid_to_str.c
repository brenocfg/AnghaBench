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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int TIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

char *
child_pid_to_str (ptid_t ptid)
{
  static char buf[40];

  sprintf (buf, "process %d thread %d", PIDGET (ptid), TIDGET (ptid));

  return buf;
}