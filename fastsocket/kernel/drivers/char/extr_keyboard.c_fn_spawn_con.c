#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * pid; int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 scalar_t__ kill_pid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ vt_spawn_con ; 

__attribute__((used)) static void fn_spawn_con(struct vc_data *vc)
{
	spin_lock(&vt_spawn_con.lock);
	if (vt_spawn_con.pid)
		if (kill_pid(vt_spawn_con.pid, vt_spawn_con.sig, 1)) {
			put_pid(vt_spawn_con.pid);
			vt_spawn_con.pid = NULL;
		}
	spin_unlock(&vt_spawn_con.lock);
}