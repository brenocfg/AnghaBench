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

/* Variables and functions */
 int /*<<< orphan*/  FEATURES ; 
 char* msp_default_features ; 
 char* prom_getenv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *get_features(void)
{
	char *feature = prom_getenv(FEATURES);

	if (feature == NULL) {
		/* default features based on MACHINE_TYPE */
		feature = msp_default_features;
	}

	return feature;
}