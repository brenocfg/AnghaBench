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
struct mv88e6xxx_priv_state {int /*<<< orphan*/  stats_mutex; int /*<<< orphan*/  smi_mutex; } ;
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int mv88e6131_setup_global (struct dsa_switch*) ; 
 int mv88e6131_setup_port (struct dsa_switch*,int) ; 
 int mv88e6131_switch_reset (struct dsa_switch*) ; 
 int /*<<< orphan*/  mv88e6xxx_ppu_state_init (struct dsa_switch*) ; 

__attribute__((used)) static int mv88e6131_setup(struct dsa_switch *ds)
{
	struct mv88e6xxx_priv_state *ps = (void *)(ds + 1);
	int i;
	int ret;

	mutex_init(&ps->smi_mutex);
	mv88e6xxx_ppu_state_init(ds);
	mutex_init(&ps->stats_mutex);

	ret = mv88e6131_switch_reset(ds);
	if (ret < 0)
		return ret;

	/* @@@ initialise vtu and atu */

	ret = mv88e6131_setup_global(ds);
	if (ret < 0)
		return ret;

	for (i = 0; i < 11; i++) {
		ret = mv88e6131_setup_port(ds, i);
		if (ret < 0)
			return ret;
	}

	return 0;
}