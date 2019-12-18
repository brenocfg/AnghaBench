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
struct kparam_string {int /*<<< orphan*/  maxlen; int /*<<< orphan*/  string; } ;
struct kernel_param {struct kparam_string* str; } ;

/* Variables and functions */
 int strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int param_get_string(char *buffer, struct kernel_param *kp)
{
	const struct kparam_string *kps = kp->str;
	return strlcpy(buffer, kps->string, kps->maxlen);
}