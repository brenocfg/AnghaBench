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
struct TYPE_2__ {int /*<<< orphan*/  user_dsos; int /*<<< orphan*/  kernel_dsos; } ;
struct perf_session {int /*<<< orphan*/  machines; TYPE_1__ host_machine; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t __dsos__fprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t machines__fprintf_dsos (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

size_t perf_session__fprintf_dsos(struct perf_session *self, FILE *fp)
{
	return __dsos__fprintf(&self->host_machine.kernel_dsos, fp) +
	       __dsos__fprintf(&self->host_machine.user_dsos, fp) +
	       machines__fprintf_dsos(&self->machines, fp);
}