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
struct tomoyo_domain_info {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  security ; 
 struct tomoyo_domain_info* task_cred_xxx (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct tomoyo_domain_info *tomoyo_real_domain(struct task_struct
							    *task)
{
	return task_cred_xxx(task, security);
}