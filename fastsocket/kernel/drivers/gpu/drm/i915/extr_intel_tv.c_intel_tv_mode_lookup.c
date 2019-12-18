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
struct tv_mode {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tv_mode*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct tv_mode* tv_modes ; 

__attribute__((used)) static const struct tv_mode *
intel_tv_mode_lookup(const char *tv_format)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(tv_modes); i++) {
		const struct tv_mode *tv_mode = &tv_modes[i];

		if (!strcmp(tv_format, tv_mode->name))
			return tv_mode;
	}
	return NULL;
}