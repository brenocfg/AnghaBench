#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* uthread_t ;
typedef  int /*<<< orphan*/ * thread_t ;
typedef  TYPE_3__* proc_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_uthlist; } ;
struct TYPE_6__ {int /*<<< orphan*/ * vc_thread; } ;
struct TYPE_7__ {TYPE_1__ uu_context; } ;

/* Variables and functions */
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 

thread_t
proc_thread(proc_t proc)                                                
{           
        uthread_t uth = TAILQ_FIRST(&proc->p_uthlist);

        if (uth != NULL)
                return(uth->uu_context.vc_thread);

	return(NULL);
}