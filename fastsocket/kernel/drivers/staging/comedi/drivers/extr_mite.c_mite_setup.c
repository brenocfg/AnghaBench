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
struct mite_struct {int dummy; } ;

/* Variables and functions */
 int mite_setup2 (struct mite_struct*,int /*<<< orphan*/ ) ; 

int mite_setup(struct mite_struct *mite)
{
	return mite_setup2(mite, 0);
}