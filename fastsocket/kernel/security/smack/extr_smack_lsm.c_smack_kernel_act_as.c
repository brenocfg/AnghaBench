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
struct cred {char* security; } ;

/* Variables and functions */
 int EINVAL ; 
 char* smack_from_secid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_kernel_act_as(struct cred *new, u32 secid)
{
	char *smack = smack_from_secid(secid);

	if (smack == NULL)
		return -EINVAL;

	new->security = smack;
	return 0;
}