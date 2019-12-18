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
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int DLM_BADARGS ; 
 int DLM_BADPARAM ; 
 int DLM_IVBUFLEN ; 
 int DLM_NOLOCKMGR ; 
 int DLM_SYSERR ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 scalar_t__ o2net_link_down (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline enum dlm_status dlm_err_to_dlm_status(int err)
{
	enum dlm_status ret;
	if (err == -ENOMEM)
		ret = DLM_SYSERR;
	else if (err == -ETIMEDOUT || o2net_link_down(err, NULL))
		ret = DLM_NOLOCKMGR;
	else if (err == -EINVAL)
		ret = DLM_BADPARAM;
	else if (err == -ENAMETOOLONG)
		ret = DLM_IVBUFLEN;
	else
		ret = DLM_BADARGS;
	return ret;
}