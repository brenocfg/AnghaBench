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
struct u132_endp {int /*<<< orphan*/  kref; int /*<<< orphan*/  scheduler; } ;
struct u132 {int dummy; } ;

/* Variables and functions */
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u132_endp_delete ; 

__attribute__((used)) static void u132_endp_cancel_work(struct u132 *u132, struct u132_endp *endp)
{
	if (cancel_delayed_work(&endp->scheduler))
		kref_put(&endp->kref, u132_endp_delete);
}