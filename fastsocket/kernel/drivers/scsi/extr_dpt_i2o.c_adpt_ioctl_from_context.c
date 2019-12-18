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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/ ** ioctl_reply_context; } ;
typedef  TYPE_1__ adpt_hba ;

/* Variables and functions */

__attribute__((used)) static void *adpt_ioctl_from_context(adpt_hba *pHba, u32 context)
{
#if BITS_PER_LONG == 32
	return (void *)(unsigned long)context;
#else
	void *p = pHba->ioctl_reply_context[context];
	pHba->ioctl_reply_context[context] = NULL;

	return p;
#endif
}