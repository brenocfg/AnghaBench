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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smack_to_secid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_security (struct task_struct*) ; 

__attribute__((used)) static void smack_task_getsecid(struct task_struct *p, u32 *secid)
{
	*secid = smack_to_secid(task_security(p));
}