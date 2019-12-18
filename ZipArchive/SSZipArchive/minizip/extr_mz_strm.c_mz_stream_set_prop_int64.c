#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* vtbl; } ;
typedef  TYPE_2__ mz_stream ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_prop_int64 ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t mz_stream_set_prop_int64(void *stream, int32_t prop, int64_t value)
{
    mz_stream *strm = (mz_stream *)stream;
    if (strm == NULL || strm->vtbl == NULL || strm->vtbl->set_prop_int64 == NULL)
        return MZ_PARAM_ERROR;
    return strm->vtbl->set_prop_int64(stream, prop, value);
}