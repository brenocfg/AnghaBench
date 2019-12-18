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
 int emu_read_config (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_region_override(const char *media_fname)
{
	// we only need to override region if config tells us so
	int ret = emu_read_config(media_fname, 0);
	if (!ret) emu_read_config(NULL, 0);
}