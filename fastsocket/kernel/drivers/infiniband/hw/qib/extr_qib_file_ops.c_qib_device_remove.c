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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qib_diag_remove (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_user_remove (struct qib_devdata*) ; 

void qib_device_remove(struct qib_devdata *dd)
{
	qib_user_remove(dd);
	qib_diag_remove(dd);
}