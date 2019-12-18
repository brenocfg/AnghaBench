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
 int /*<<< orphan*/  fname_ext (char*,int,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rom_fname_loaded ; 

__attribute__((used)) static void romfname_ext(char *dst, int dstlen, const char *prefix, const char *ext)
{
	fname_ext(dst, dstlen, prefix, ext, rom_fname_loaded);
}