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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  EM_ASM (int) ; 
 int* Module ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_main ; 

int main()
{
	// Bad bad bad to sleep on the main thread, but test that it works.
	Sleep(1);
	Sleep(10);
	Sleep(100);
	Sleep(1000);
	Sleep(5000);
	pthread_t thread;
	pthread_create(&thread, NULL, thread_main, NULL);
	EM_ASM(Module['noExitRuntime']=true);
}