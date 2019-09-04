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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ (* read_seek ) (int /*<<< orphan*/ ,int,scalar_t__,int) ;scalar_t__ (* seek ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ pos; int /*<<< orphan*/  opaque; int /*<<< orphan*/  buf_end; int /*<<< orphan*/  buf_ptr; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int64_t avio_seek_time(AVIOContext *s, int stream_index,
                       int64_t timestamp, int flags)
{
    int64_t ret;
    if (!s->read_seek)
        return AVERROR(ENOSYS);
    ret = s->read_seek(s->opaque, stream_index, timestamp, flags);
    if (ret >= 0) {
        int64_t pos;
        s->buf_ptr = s->buf_end; // Flush buffer
        pos = s->seek(s->opaque, 0, SEEK_CUR);
        if (pos >= 0)
            s->pos = pos;
        else if (pos != AVERROR(ENOSYS))
            ret = pos;
    }
    return ret;
}