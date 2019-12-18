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
 int UT_CANCEL ; 
 int UT_CANCELDISABLE ; 
 int UT_CANCELED ; 

__attribute__((used)) static int
uthread_is_cancelled(struct uthread *t)
{
	return (t->uu_flag & (UT_CANCELDISABLE | UT_CANCEL | UT_CANCELED)) == UT_CANCEL;
}