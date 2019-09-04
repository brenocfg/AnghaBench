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
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
struct TYPE_3__ {void* stsy_return; void* stsy_entry; int /*<<< orphan*/ * stsy_underlying; } ;

/* Variables and functions */
 void* DTRACE_IDNONE ; 
 unsigned int NSYSCALL ; 
 int /*<<< orphan*/  SYSTRACE_ARTIFICIAL_FRAMES ; 
 scalar_t__ SYSTRACE_ENTRY (unsigned int) ; 
 scalar_t__ SYSTRACE_RETURN (unsigned int) ; 
 int /*<<< orphan*/  dtrace_probe_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * syscallnames ; 
 int /*<<< orphan*/  sysent ; 
 int /*<<< orphan*/  systrace_id ; 
 int /*<<< orphan*/  systrace_init (int /*<<< orphan*/ ,TYPE_1__**) ; 
 TYPE_1__* systrace_sysent ; 

__attribute__((used)) static void
systrace_provide(void *arg, const dtrace_probedesc_t *desc)
{
#pragma unused(arg) /* __APPLE__ */
	unsigned int i;

	if (desc != NULL)
		return;

	systrace_init(sysent, &systrace_sysent);

	for (i = 0; i < NSYSCALL; i++) {
		if (systrace_sysent[i].stsy_underlying == NULL)
			continue;

		if (dtrace_probe_lookup(systrace_id, NULL,
		    syscallnames[i], "entry") != 0)
			continue;

		(void) dtrace_probe_create(systrace_id, NULL, syscallnames[i],
		    "entry", SYSTRACE_ARTIFICIAL_FRAMES,
		    (void *)((uintptr_t)SYSTRACE_ENTRY(i)));
		(void) dtrace_probe_create(systrace_id, NULL, syscallnames[i],
		    "return", SYSTRACE_ARTIFICIAL_FRAMES,
		    (void *)((uintptr_t)SYSTRACE_RETURN(i)));

		systrace_sysent[i].stsy_entry = DTRACE_IDNONE;
		systrace_sysent[i].stsy_return = DTRACE_IDNONE;
	}
}