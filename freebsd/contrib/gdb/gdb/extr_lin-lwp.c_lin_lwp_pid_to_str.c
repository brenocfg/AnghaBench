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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 scalar_t__ is_lwp (int /*<<< orphan*/ ) ; 
 char* normal_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
lin_lwp_pid_to_str (ptid_t ptid)
{
  static char buf[64];

  if (is_lwp (ptid))
    {
      snprintf (buf, sizeof (buf), "LWP %ld", GET_LWP (ptid));
      return buf;
    }

  return normal_pid_to_str (ptid);
}