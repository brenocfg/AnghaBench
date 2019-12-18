#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* user_ldt_t ;
typedef  scalar_t__ uint16_t ;
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* task_t ;
struct real_descriptor {int dummy; } ;
struct TYPE_9__ {scalar_t__ limit_low; } ;
struct TYPE_8__ {TYPE_1__* i386_ldt; } ;
struct TYPE_7__ {TYPE_3__* task; } ;
struct TYPE_6__ {size_t start; int count; int /*<<< orphan*/  ldt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_LDT ; 
 size_t LDTSZ_MIN ; 
 int /*<<< orphan*/  USER_LDT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct real_descriptor*,int) ; 
 int /*<<< orphan*/  bzero (struct real_descriptor*,int) ; 
 scalar_t__ current_ldt () ; 
 TYPE_5__* gdt_desc_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_cpu_set_ldt (int /*<<< orphan*/ ) ; 

void
user_ldt_set(
	thread_t thread)
{
        task_t		task = thread->task;
	user_ldt_t	user_ldt;

	user_ldt = task->i386_ldt;

	if (user_ldt != 0) {
	    struct real_descriptor *ldtp = (struct real_descriptor *)current_ldt();

	    if (user_ldt->start > LDTSZ_MIN) {
		bzero(&ldtp[LDTSZ_MIN],
		      sizeof(struct real_descriptor) * (user_ldt->start - LDTSZ_MIN));
	    }
	    
	    bcopy(user_ldt->ldt, &ldtp[user_ldt->start],
		  sizeof(struct real_descriptor) * (user_ldt->count));

	    gdt_desc_p(USER_LDT)->limit_low = (uint16_t)((sizeof(struct real_descriptor) * (user_ldt->start + user_ldt->count)) - 1);

	    ml_cpu_set_ldt(USER_LDT);
	} else {
	    ml_cpu_set_ldt(KERNEL_LDT);
	}
}