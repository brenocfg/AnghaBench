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
struct shared_info {int /*<<< orphan*/ * evtchn_pending; } ;

/* Variables and functions */
 struct shared_info* HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  sync_clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_evtchn(int port)
{
	struct shared_info *s = HYPERVISOR_shared_info;
	sync_clear_bit(port, &s->evtchn_pending[0]);
}