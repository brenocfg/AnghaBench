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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  size_pos; } ;
typedef  TYPE_1__ ID3v2EncContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int av_clip (int,int,scalar_t__) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  id3v2_put_size (int /*<<< orphan*/ *,scalar_t__) ; 

void ff_id3v2_finish(ID3v2EncContext *id3, AVIOContext *pb,
                     int padding_bytes)
{
    int64_t cur_pos;

    if (padding_bytes < 0)
        padding_bytes = 10;

    /* The ID3v2.3 specification states that 28 bits are used to represent the
     * size of the whole tag.  Therefore the current size of the tag needs to be
     * subtracted from the upper limit of 2^28-1 to clip the value correctly. */
    /* The minimum of 10 is an arbitrary amount of padding at the end of the tag
     * to fix cover art display with some software such as iTunes, Traktor,
     * Serato, Torq. */
    padding_bytes = av_clip(padding_bytes, 10, 268435455 - id3->len);
    ffio_fill(pb, 0, padding_bytes);
    id3->len += padding_bytes;

    cur_pos = avio_tell(pb);
    avio_seek(pb, id3->size_pos, SEEK_SET);
    id3v2_put_size(pb, id3->len);
    avio_seek(pb, cur_pos, SEEK_SET);
}