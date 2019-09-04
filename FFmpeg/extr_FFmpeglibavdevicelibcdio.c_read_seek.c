#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {TYPE_2__** streams; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  cur_dts; } ;
struct TYPE_5__ {int /*<<< orphan*/  paranoia; } ;
typedef  TYPE_1__ CDIOContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  cdio_paranoia_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_seek(AVFormatContext *ctx, int stream_index, int64_t timestamp,
                     int flags)
{
    CDIOContext *s = ctx->priv_data;
    AVStream *st = ctx->streams[0];

    cdio_paranoia_seek(s->paranoia, timestamp, SEEK_SET);
    st->cur_dts = timestamp;
    return 0;
}