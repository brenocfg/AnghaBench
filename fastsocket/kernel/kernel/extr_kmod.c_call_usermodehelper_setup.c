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
struct subprocess_info {char* path; char** argv; char** envp; int /*<<< orphan*/  cred; int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __call_usermodehelper ; 
 int /*<<< orphan*/  kfree (struct subprocess_info*) ; 
 struct subprocess_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_usermodehelper_creds () ; 

struct subprocess_info *call_usermodehelper_setup(char *path, char **argv,
						  char **envp, gfp_t gfp_mask)
{
	struct subprocess_info *sub_info;
	sub_info = kzalloc(sizeof(struct subprocess_info), gfp_mask);
	if (!sub_info)
		goto out;

	INIT_WORK(&sub_info->work, __call_usermodehelper);
	sub_info->path = path;
	sub_info->argv = argv;
	sub_info->envp = envp;
	sub_info->cred = prepare_usermodehelper_creds();
	if (!sub_info->cred) {
		kfree(sub_info);
		return NULL;
	}

  out:
	return sub_info;
}