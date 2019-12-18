#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_owner_match_info {int match; int invert; scalar_t__ uid_min; scalar_t__ uid_max; scalar_t__ gid_min; scalar_t__ gid_max; } ;
struct xt_match_param {struct xt_owner_match_info* matchinfo; } ;
struct sk_buff {TYPE_2__* sk; } ;
struct file {TYPE_3__* f_cred; } ;
struct TYPE_6__ {scalar_t__ fsuid; scalar_t__ fsgid; } ;
struct TYPE_5__ {TYPE_1__* sk_socket; } ;
struct TYPE_4__ {struct file* file; } ;

/* Variables and functions */
 int XT_OWNER_GID ; 
 int XT_OWNER_SOCKET ; 
 int XT_OWNER_UID ; 

__attribute__((used)) static bool
owner_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_owner_match_info *info = par->matchinfo;
	const struct file *filp;

	if (skb->sk == NULL || skb->sk->sk_socket == NULL)
		return (info->match ^ info->invert) == 0;
	else if (info->match & info->invert & XT_OWNER_SOCKET)
		/*
		 * Socket exists but user wanted ! --socket-exists.
		 * (Single ampersands intended.)
		 */
		return false;

	filp = skb->sk->sk_socket->file;
	if (filp == NULL)
		return ((info->match ^ info->invert) &
		       (XT_OWNER_UID | XT_OWNER_GID)) == 0;

	if (info->match & XT_OWNER_UID)
		if ((filp->f_cred->fsuid >= info->uid_min &&
		    filp->f_cred->fsuid <= info->uid_max) ^
		    !(info->invert & XT_OWNER_UID))
			return false;

	if (info->match & XT_OWNER_GID)
		if ((filp->f_cred->fsgid >= info->gid_min &&
		    filp->f_cred->fsgid <= info->gid_max) ^
		    !(info->invert & XT_OWNER_GID))
			return false;

	return true;
}