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
struct sdram_params {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sdram_params*) ; 
 struct sdram_params* sdram_tbl ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sdram_params *sa1110_find_sdram(const char *name)
{
	struct sdram_params *sdram;

	for (sdram = sdram_tbl; sdram < sdram_tbl + ARRAY_SIZE(sdram_tbl); sdram++)
		if (strcmp(name, sdram->name) == 0)
			return sdram;

	return NULL;
}