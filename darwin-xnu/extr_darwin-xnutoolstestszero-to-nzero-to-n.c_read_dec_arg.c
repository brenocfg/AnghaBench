#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* g_longopts ; 
 char* optarg ; 
 size_t option_index ; 
 int /*<<< orphan*/  strtoull (char*,char**,int) ; 

__attribute__((used)) static uint32_t
read_dec_arg()
{
	char *cp;
	/* char* optarg is a magic global */

	uint32_t arg_val = (uint32_t)strtoull(optarg, &cp, 10);

	if (cp == optarg || *cp)
		errx(EX_USAGE, "arg --%s requires a decimal number, found \"%s\"",
		     g_longopts[option_index].name, optarg);

	return arg_val;
}