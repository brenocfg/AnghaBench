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
struct sh_tmu_priv {int dummy; } ;
struct clock_event_device {int mode; int /*<<< orphan*/  name; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
#define  CLOCK_EVT_MODE_ONESHOT 131 
#define  CLOCK_EVT_MODE_PERIODIC 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 struct sh_tmu_priv* ced_to_sh_tmu (struct clock_event_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_tmu_clock_event_start (struct sh_tmu_priv*,int) ; 
 int /*<<< orphan*/  sh_tmu_disable (struct sh_tmu_priv*) ; 

__attribute__((used)) static void sh_tmu_clock_event_mode(enum clock_event_mode mode,
				    struct clock_event_device *ced)
{
	struct sh_tmu_priv *p = ced_to_sh_tmu(ced);
	int disabled = 0;

	/* deal with old setting first */
	switch (ced->mode) {
	case CLOCK_EVT_MODE_PERIODIC:
	case CLOCK_EVT_MODE_ONESHOT:
		sh_tmu_disable(p);
		disabled = 1;
		break;
	default:
		break;
	}

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		pr_info("sh_tmu: %s used for periodic clock events\n",
			ced->name);
		sh_tmu_clock_event_start(p, 1);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		pr_info("sh_tmu: %s used for oneshot clock events\n",
			ced->name);
		sh_tmu_clock_event_start(p, 0);
		break;
	case CLOCK_EVT_MODE_UNUSED:
		if (!disabled)
			sh_tmu_disable(p);
		break;
	case CLOCK_EVT_MODE_SHUTDOWN:
	default:
		break;
	}
}