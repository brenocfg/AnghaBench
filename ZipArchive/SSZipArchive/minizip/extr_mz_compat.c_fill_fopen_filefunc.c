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

/* Variables and functions */
 int /*<<< orphan*/  mz_stream_os_get_interface () ; 

void fill_fopen_filefunc(zlib_filefunc_def *pzlib_filefunc_def)
{
    if (pzlib_filefunc_def != NULL)
        *pzlib_filefunc_def = mz_stream_os_get_interface();
}