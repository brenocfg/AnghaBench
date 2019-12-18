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
struct uthread {int uu_flag; } ;

/* Variables and functions */
 int IOPOL_ATIME_UPDATES_DEFAULT ; 
 int IOPOL_ATIME_UPDATES_OFF ; 
 int UT_ATIME_UPDATE ; 

__attribute__((used)) static inline int
get_thread_atime_policy(struct uthread *ut)
{
	return (ut->uu_flag & UT_ATIME_UPDATE)? IOPOL_ATIME_UPDATES_OFF: IOPOL_ATIME_UPDATES_DEFAULT;
}