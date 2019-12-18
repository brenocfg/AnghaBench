#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int ffio_close_null_buf (int /*<<< orphan*/ *) ; 
 int ffio_open_null_buf (int /*<<< orphan*/ **) ; 
 int mov_write_moov_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int get_moov_size(AVFormatContext *s)
{
    int ret;
    AVIOContext *moov_buf;
    MOVMuxContext *mov = s->priv_data;

    if ((ret = ffio_open_null_buf(&moov_buf)) < 0)
        return ret;
    if ((ret = mov_write_moov_tag(moov_buf, mov, s)) < 0)
        return ret;
    return ffio_close_null_buf(moov_buf);
}