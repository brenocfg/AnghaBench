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
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {scalar_t__ buffer_len; int /*<<< orphan*/  buffer; TYPE_1__ stream; } ;
typedef  TYPE_2__ mz_stream_zlib ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_WRITE_ERROR ; 
 scalar_t__ mz_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int32_t mz_stream_zlib_flush(void *stream)
{
    mz_stream_zlib *zlib = (mz_stream_zlib *)stream;
    if (mz_stream_write(zlib->stream.base, zlib->buffer, zlib->buffer_len) != zlib->buffer_len)
        return MZ_WRITE_ERROR;
    return MZ_OK;
}