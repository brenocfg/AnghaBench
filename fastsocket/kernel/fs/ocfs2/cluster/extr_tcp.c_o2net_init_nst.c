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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;
struct o2net_send_tracking {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void o2net_init_nst(struct o2net_send_tracking *nst, u32 msgtype,
				  u32 msgkey, struct task_struct *task, u8 node)
{
}