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
typedef  int /*<<< orphan*/  thread_info ;
typedef  int /*<<< orphan*/  lwpid_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_thread_info (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_thread_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static thread_info *
add_tthread (int pid, lwpid_t tid)
{
  thread_info *p;

  p = find_thread_info (tid);
  if (NULL == p)
    p = create_thread_info (pid, tid);

  return p;
}