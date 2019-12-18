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
struct TYPE_3__ {char option; int /*<<< orphan*/  help_text; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  info (char*,...) ; 
 TYPE_1__* menu ; 

__attribute__((used)) static int show_help(void)
{
	unsigned int i;
	char parameters[ARRAY_SIZE(menu) + 1];

	for (i = 0; i < ARRAY_SIZE(menu); i++)
		parameters[i] = menu[i].option;

	parameters[ARRAY_SIZE(menu)] = '\0';

	info("usage: ar9170user -[%s]\n", parameters);

	for (i = 0; i < ARRAY_SIZE(menu); i++)
		info("\t-%c\t%s\n", menu[i].option, menu[i].help_text);

	return EXIT_FAILURE;
}