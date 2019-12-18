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
typedef  int /*<<< orphan*/  zlib_filefunc_def ;
typedef  int /*<<< orphan*/  unzFile ;

/* Variables and functions */
 int /*<<< orphan*/  unzOpen2_64 (char const*,int /*<<< orphan*/ *) ; 

unzFile unzOpen2(const char *path, zlib_filefunc_def *pzlib_filefunc_def)
{
    return unzOpen2_64(path, pzlib_filefunc_def);
}