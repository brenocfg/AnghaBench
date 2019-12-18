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
struct i2c_child_t {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  envctrl_set_mon (struct i2c_child_t*,char const*,int /*<<< orphan*/ ) ; 
 void* of_get_property (struct device_node*,char*,int*) ; 
 unsigned int shutdown_temperature ; 
 int strlen (char const*) ; 
 unsigned int warning_temperature ; 

__attribute__((used)) static void envctrl_init_adc(struct i2c_child_t *pchild, struct device_node *dp)
{
	int i = 0, len;
	const char *pos;
	const unsigned int *pval;

	/* Firmware describe channels into a stream separated by a '\0'. */
	pos = of_get_property(dp, "channels-description", &len);

	while (len > 0) {
		int l = strlen(pos) + 1;
		envctrl_set_mon(pchild, pos, i++);
		len -= l;
		pos += l;
	}

	/* Get optional properties. */
	pval = of_get_property(dp, "warning-temp", NULL);
	if (pval)
		warning_temperature = *pval;

	pval = of_get_property(dp, "shutdown-temp", NULL);
	if (pval)
		shutdown_temperature = *pval;
}