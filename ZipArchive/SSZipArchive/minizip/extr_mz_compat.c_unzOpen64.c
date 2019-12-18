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
typedef  int /*<<< orphan*/  zlib_filefunc64_def ;
typedef  int /*<<< orphan*/  unzFile ;

/* Variables and functions */
 int /*<<< orphan*/  mz_stream_os_get_interface () ; 
 int /*<<< orphan*/  unzOpen2 (void const*,int /*<<< orphan*/ *) ; 

unzFile unzOpen64(const void *path)
{
    zlib_filefunc64_def pzlib = mz_stream_os_get_interface();
    return unzOpen2(path, &pzlib);
}