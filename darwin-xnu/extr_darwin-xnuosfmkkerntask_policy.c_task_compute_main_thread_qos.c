#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* task_t ;
struct TYPE_4__ {int trp_qos_clamp; int trp_apptype; } ;
struct TYPE_5__ {scalar_t__ bsd_info; TYPE_1__ requested_policy; } ;

/* Variables and functions */
 int MAX (int,int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
#define  TASK_APPTYPE_APP_DEFAULT 133 
#define  TASK_APPTYPE_APP_TAL 132 
#define  TASK_APPTYPE_DAEMON_ADAPTIVE 131 
#define  TASK_APPTYPE_DAEMON_BACKGROUND 130 
#define  TASK_APPTYPE_DAEMON_INTERACTIVE 129 
#define  TASK_APPTYPE_DAEMON_STANDARD 128 
 int THREAD_QOS_BACKGROUND ; 
 int THREAD_QOS_LEGACY ; 
 int THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  THREAD_QOS_USER_INITIATED ; 
 int THREAD_QOS_USER_INTERACTIVE ; 
 scalar_t__ initproc ; 

int
task_compute_main_thread_qos(task_t task)
{
	int primordial_qos = THREAD_QOS_UNSPECIFIED;

	int qos_clamp = task->requested_policy.trp_qos_clamp;

	switch (task->requested_policy.trp_apptype) {
		case TASK_APPTYPE_APP_TAL:
		case TASK_APPTYPE_APP_DEFAULT:
			primordial_qos = THREAD_QOS_USER_INTERACTIVE;
			break;

		case TASK_APPTYPE_DAEMON_INTERACTIVE:
		case TASK_APPTYPE_DAEMON_STANDARD:
		case TASK_APPTYPE_DAEMON_ADAPTIVE:
			primordial_qos = THREAD_QOS_LEGACY;
			break;

		case TASK_APPTYPE_DAEMON_BACKGROUND:
			primordial_qos = THREAD_QOS_BACKGROUND;
			break;
	}

	if (task->bsd_info == initproc) {
		/* PID 1 gets a special case */
		primordial_qos = MAX(primordial_qos, THREAD_QOS_USER_INITIATED);
	}

	if (qos_clamp != THREAD_QOS_UNSPECIFIED) {
		if (primordial_qos != THREAD_QOS_UNSPECIFIED) {
			primordial_qos = MIN(qos_clamp, primordial_qos);
		} else {
			primordial_qos = qos_clamp;
		}
	}

	return primordial_qos;
}