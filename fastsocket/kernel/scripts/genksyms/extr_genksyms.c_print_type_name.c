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
typedef  enum symbol_type { ____Placeholder_symbol_type } symbol_type ;

/* Variables and functions */
 int SYM_NORMAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char** symbol_type_name ; 

__attribute__((used)) static void print_type_name(enum symbol_type type, const char *name)
{
	if (type != SYM_NORMAL)
		fprintf(stderr, "%s %s", symbol_type_name[type], name);
	else
		fprintf(stderr, "%s", name);
}