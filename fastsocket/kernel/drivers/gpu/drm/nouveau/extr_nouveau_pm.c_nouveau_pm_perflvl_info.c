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
typedef  int /*<<< orphan*/  v ;
struct nouveau_pm_level {int core; int shader; int memory; int volt_min; int volt_max; int fanspeed; } ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  m ;
typedef  int /*<<< orphan*/  f ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
nouveau_pm_perflvl_info(struct nouveau_pm_level *perflvl, char *ptr, int len)
{
	char c[16], s[16], v[32], f[16], m[16];

	c[0] = '\0';
	if (perflvl->core)
		snprintf(c, sizeof(c), " core %dMHz", perflvl->core / 1000);

	s[0] = '\0';
	if (perflvl->shader)
		snprintf(s, sizeof(s), " shader %dMHz", perflvl->shader / 1000);

	m[0] = '\0';
	if (perflvl->memory)
		snprintf(m, sizeof(m), " memory %dMHz", perflvl->memory / 1000);

	v[0] = '\0';
	if (perflvl->volt_min && perflvl->volt_min != perflvl->volt_max) {
		snprintf(v, sizeof(v), " voltage %dmV-%dmV",
			 perflvl->volt_min / 1000, perflvl->volt_max / 1000);
	} else
	if (perflvl->volt_min) {
		snprintf(v, sizeof(v), " voltage %dmV",
			 perflvl->volt_min / 1000);
	}

	f[0] = '\0';
	if (perflvl->fanspeed)
		snprintf(f, sizeof(f), " fanspeed %d%%", perflvl->fanspeed);

	snprintf(ptr, len, "%s%s%s%s%s\n", c, s, m, v, f);
}