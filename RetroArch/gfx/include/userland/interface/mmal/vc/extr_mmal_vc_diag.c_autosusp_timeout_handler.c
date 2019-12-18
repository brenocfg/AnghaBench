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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int autosusp_signal ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void autosusp_timeout_handler(int cause, siginfo_t *how, void *ucontext)
{
   (void)how; (void)ucontext; (void)cause;
   printf("Sending signal %d\n", autosusp_signal);
   kill(getpid(), autosusp_signal);
}