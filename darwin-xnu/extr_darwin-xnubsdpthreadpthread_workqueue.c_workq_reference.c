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
struct workqueue {int /*<<< orphan*/  wq_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_ref_retain (int /*<<< orphan*/ *) ; 

void
workq_reference(struct workqueue *wq)
{
	os_ref_retain(&wq->wq_refcnt);
}