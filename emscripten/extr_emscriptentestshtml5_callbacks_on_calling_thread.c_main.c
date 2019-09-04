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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mainRuntimeThreadId ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  threadMain ; 

int main()
{
  mainRuntimeThreadId = pthread_self();

  pthread_t thread;
  int rc = pthread_create(&thread, NULL, threadMain, 0);
  assert(rc == 0);

  EM_ASM(Module['noExitRuntime'] = true);
}