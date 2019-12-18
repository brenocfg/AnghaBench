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
struct TYPE_3__ {int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int ffio_close_null_buf (int /*<<< orphan*/ *) ; 
 int ffio_open_null_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mov_write_sidx_tags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_sidx_size(AVFormatContext *s)
{
    int ret;
    AVIOContext *buf;
    MOVMuxContext *mov = s->priv_data;

    if ((ret = ffio_open_null_buf(&buf)) < 0)
        return ret;
    mov_write_sidx_tags(buf, mov, -1, 0);
    return ffio_close_null_buf(buf);
}