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
struct sswt_cb {int timeflag; int /*<<< orphan*/ * psem; } ;

/* Variables and functions */
 int /*<<< orphan*/  sys_sem_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sswt_handler(void *arg)
{
    struct sswt_cb *sswt_cb = (struct sswt_cb *) arg;

    /* Timeout. Set flag to TRUE and signal semaphore */
    sswt_cb->timeflag = 1;
    sys_sem_signal(*(sswt_cb->psem));
}