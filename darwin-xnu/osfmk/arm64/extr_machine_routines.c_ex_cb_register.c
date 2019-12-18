#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/ * ex_cb_t ;
struct TYPE_3__ {void* refcon; int /*<<< orphan*/ * cb; } ;
typedef  TYPE_1__ ex_cb_info_t ;
typedef  size_t ex_cb_class_t ;

/* Variables and functions */
 size_t EXCB_CLASS_MAX ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* ex_cb_info ; 

kern_return_t ex_cb_register(
	ex_cb_class_t	cb_class,
	ex_cb_t			cb,
	void			*refcon)
{
	ex_cb_info_t *pInfo = &ex_cb_info[cb_class];

	if ((NULL == cb) || (cb_class >= EXCB_CLASS_MAX))
	{
		return KERN_INVALID_VALUE;
	}

	if (NULL == pInfo->cb)
	{
		pInfo->cb = cb;
		pInfo->refcon = refcon;
		return KERN_SUCCESS;
	}
	return KERN_FAILURE;
}