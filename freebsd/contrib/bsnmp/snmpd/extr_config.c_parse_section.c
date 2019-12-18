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
struct lmodule {char* section; } ;

/* Variables and functions */
 scalar_t__ TOK_STR ; 
 int /*<<< orphan*/  gettoken () ; 
 int ignore ; 
 int /*<<< orphan*/  report (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strval ; 
 scalar_t__ token ; 

__attribute__((used)) static void
parse_section(const struct lmodule *mod)
{
	if (token != TOK_STR)
		report("expecting section name");

	if (strcmp(strval, "snmpd") == 0) {
		if (mod != NULL)
			/* loading a module - ignore common stuff */
			ignore = 1;
		else
			/* global configuration - don't ignore */
			ignore = 0;
	} else {
		if (mod == NULL) {
			/* global configuration - ignore module stuff */
			ignore = 1;
		} else {
			/* loading module - check if it's our section */
			ignore = (strcmp(strval, mod->section) != 0);
		}
	}
	gettoken();
}