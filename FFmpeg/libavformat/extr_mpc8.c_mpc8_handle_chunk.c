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
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
#define  TAG_SEEKTBLOFF 128 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ ffio_read_varlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc8_parse_seektable (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void mpc8_handle_chunk(AVFormatContext *s, int tag, int64_t chunk_pos, int64_t size)
{
    AVIOContext *pb = s->pb;
    int64_t pos, off;

    switch(tag){
    case TAG_SEEKTBLOFF:
        pos = avio_tell(pb) + size;
        off = ffio_read_varlen(pb);
        mpc8_parse_seektable(s, chunk_pos + off);
        avio_seek(pb, pos, SEEK_SET);
        break;
    default:
        avio_skip(pb, size);
    }
}