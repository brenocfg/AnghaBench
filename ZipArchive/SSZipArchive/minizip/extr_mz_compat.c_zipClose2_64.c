#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zipFile ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ * stream; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ mz_compat ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FREE (TYPE_1__*) ; 
 int MZ_OK ; 
 int /*<<< orphan*/  mz_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_delete (int /*<<< orphan*/ **) ; 
 int zipClose2_MZ (scalar_t__,char const*,int /*<<< orphan*/ ) ; 

int zipClose2_64(zipFile file, const char *global_comment, uint16_t version_madeby)
{
    mz_compat *compat = (mz_compat *)file;
    int32_t err = MZ_OK;

    if (compat->handle != NULL)
        err = zipClose2_MZ(file, global_comment, version_madeby);

    if (compat->stream != NULL)
    {
        mz_stream_close(compat->stream);
        mz_stream_delete(&compat->stream);
    }

    MZ_FREE(compat);

    return err;
}