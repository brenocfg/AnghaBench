#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int header_count; int /*<<< orphan*/  write_index; int /*<<< orphan*/  sp_count; } ;
typedef  TYPE_1__ NUTContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_STARTCODE ; 
 int /*<<< orphan*/  av_assert1 (int /*<<< orphan*/ ) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  put_packet (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_headers (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_index (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nut_write_trailer(AVFormatContext *s)
{
    NUTContext *nut = s->priv_data;
    AVIOContext *bc = s->pb, *dyn_bc;
    int ret;

    while (nut->header_count < 3)
        write_headers(s, bc);

    if (!nut->sp_count)
        return 0;

    ret = avio_open_dyn_buf(&dyn_bc);
    if (ret >= 0) {
        av_assert1(nut->write_index); // sp_count should be 0 if no index is going to be written
        write_index(nut, dyn_bc);
        put_packet(nut, bc, dyn_bc, 1, INDEX_STARTCODE);
    }

    return 0;
}