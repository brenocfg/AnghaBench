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
struct module_attribute {int dummy; } ;
struct module {int state; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  MODULE_STATE_COMING 130 
#define  MODULE_STATE_GOING 129 
#define  MODULE_STATE_LIVE 128 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static ssize_t show_initstate(struct module_attribute *mattr,
			   struct module *mod, char *buffer)
{
	const char *state = "unknown";

	switch (mod->state) {
	case MODULE_STATE_LIVE:
		state = "live";
		break;
	case MODULE_STATE_COMING:
		state = "coming";
		break;
	case MODULE_STATE_GOING:
		state = "going";
		break;
	}
	return sprintf(buffer, "%s\n", state);
}