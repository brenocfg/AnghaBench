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
struct task_security_struct {int dummy; } ;
struct cred {struct task_security_struct* security; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct task_security_struct* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_cred_alloc_blank(struct cred *cred, gfp_t gfp)
{
	struct task_security_struct *tsec;

	tsec = kzalloc(sizeof(struct task_security_struct), gfp);
	if (!tsec)
		return -ENOMEM;

	cred->security = tsec;
	return 0;
}