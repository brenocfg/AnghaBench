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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int get_pri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mach_thread_np (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setname_np (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 

__attribute__((used)) static void
set_thread_name(const char *fn_name)
{
	char name[50] = "";

	thread_t thread_port = pthread_mach_thread_np(pthread_self());

	int pri = get_pri(thread_port);

	snprintf(name, sizeof(name), "%s at pri %2d", fn_name, pri);
	pthread_setname_np(name);
}