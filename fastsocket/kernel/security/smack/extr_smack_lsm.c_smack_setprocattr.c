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
struct task_struct {int dummy; } ;
struct cred {char* security; } ;
struct TYPE_2__ {char* smk_known; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_ADMIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 size_t SMK_LABELLEN ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_creds (struct cred*) ; 
 struct task_struct* current ; 
 struct cred* prepare_creds () ; 
 TYPE_1__ smack_known_web ; 
 char* smk_import (void*,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int smack_setprocattr(struct task_struct *p, char *name,
			     void *value, size_t size)
{
	struct cred *new;
	char *newsmack;

	/*
	 * Changing another process' Smack value is too dangerous
	 * and supports no sane use case.
	 */
	if (p != current)
		return -EPERM;

	if (!capable(CAP_MAC_ADMIN))
		return -EPERM;

	if (value == NULL || size == 0 || size >= SMK_LABELLEN)
		return -EINVAL;

	if (strcmp(name, "current") != 0)
		return -EINVAL;

	newsmack = smk_import(value, size);
	if (newsmack == NULL)
		return -EINVAL;

	/*
	 * No process is ever allowed the web ("@") label.
	 */
	if (newsmack == smack_known_web.smk_known)
		return -EPERM;

	new = prepare_creds();
	if (new == NULL)
		return -ENOMEM;
	new->security = newsmack;
	commit_creds(new);
	return size;
}