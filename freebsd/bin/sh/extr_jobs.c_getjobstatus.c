#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct job {int nprocs; TYPE_1__* ps; int /*<<< orphan*/  pipefail; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */

__attribute__((used)) static int getjobstatus(const struct job *jp)
{
	int i, status;

	if (!jp->pipefail)
		return (jp->ps[jp->nprocs - 1].status);
	for (i = jp->nprocs - 1; i >= 0; i--) {
		status = jp->ps[i].status;
		if (status != 0)
			return (status);
	}
	return (0);
}