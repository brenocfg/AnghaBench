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
typedef  int /*<<< orphan*/  mm_segment_t ;

/* Variables and functions */
 int do_mod_firmware_load (char const*,char**) ; 
 int /*<<< orphan*/  get_ds () ; 
 int /*<<< orphan*/  get_fs () ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

int mod_firmware_load(const char *fn, char **fp)
{
	int r;
	mm_segment_t fs = get_fs();

	set_fs(get_ds());
	r = do_mod_firmware_load(fn, fp);
	set_fs(fs);
	return r;
}