#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {unsigned int num_substreams; } ;
typedef  TYPE_1__ MLPEncodeContext ;

/* Variables and functions */
 int MAX_SUBSTREAMS ; 
 int /*<<< orphan*/  write_frame_headers (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_major_sync (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * write_substrs (TYPE_1__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int write_access_unit(MLPEncodeContext *ctx, uint8_t *buf,
                                      int buf_size, int restart_frame)
{
    uint16_t substream_data_len[MAX_SUBSTREAMS];
    uint8_t *buf1, *buf0 = buf;
    unsigned int substr;
    int total_length;

    if (buf_size < 4)
        return -1;

    /* Frame header will be written at the end. */
    buf      += 4;
    buf_size -= 4;

    if (restart_frame) {
        if (buf_size < 28)
            return -1;
        write_major_sync(ctx, buf, buf_size);
        buf      += 28;
        buf_size -= 28;
    }

    buf1 = buf;

    /* Substream headers will be written at the end. */
    for (substr = 0; substr < ctx->num_substreams; substr++) {
        buf      += 2;
        buf_size -= 2;
    }

    buf = write_substrs(ctx, buf, buf_size, restart_frame, substream_data_len);

    total_length = buf - buf0;

    write_frame_headers(ctx, buf0, buf1, total_length / 2, restart_frame, substream_data_len);

    return total_length;
}