#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct knote {int kn_sfflags; } ;
typedef  TYPE_1__* ipc_kmsg_t ;
struct TYPE_3__ {int /*<<< orphan*/  ikm_qos_override; } ;

/* Variables and functions */
 int FILTER_ADJUST_EVENT_QOS (int) ; 
 int MACH_RCV_MSG ; 
 int _pthread_priority_thread_qos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_machport_adjust_qos(struct knote *kn, ipc_kmsg_t first)
{
	if (kn->kn_sfflags & MACH_RCV_MSG) {
		int qos = _pthread_priority_thread_qos(first->ikm_qos_override);
		return FILTER_ADJUST_EVENT_QOS(qos);
	}
	return 0;
}