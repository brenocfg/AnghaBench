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
typedef  int /*<<< orphan*/  zipFile ;

/* Variables and functions */
 int /*<<< orphan*/  zipOpen2_64 (char const*,int,char const**,int /*<<< orphan*/ *) ; 

zipFile zipOpen2(const char *path, int append, const char **globalcomment,
    zlib_filefunc_def *pzlib_filefunc_def)
{
    return zipOpen2_64(path, append, globalcomment, pzlib_filefunc_def);
}