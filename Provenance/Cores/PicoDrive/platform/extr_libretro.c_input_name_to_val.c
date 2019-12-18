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
typedef  enum input_device { ____Placeholder_input_device } input_device ;

/* Variables and functions */
 int PICO_INPUT_NOTHING ; 
 int PICO_INPUT_PAD_3BTN ; 
 int PICO_INPUT_PAD_6BTN ; 
 int /*<<< orphan*/  lprintf (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static enum input_device input_name_to_val(const char *name)
{
	if (strcmp(name, "3 button pad") == 0)
		return PICO_INPUT_PAD_3BTN;
	if (strcmp(name, "6 button pad") == 0)
		return PICO_INPUT_PAD_6BTN;
	if (strcmp(name, "None") == 0)
		return PICO_INPUT_NOTHING;

	lprintf("invalid picodrive_input: '%s'\n", name);
	return PICO_INPUT_PAD_3BTN;
}