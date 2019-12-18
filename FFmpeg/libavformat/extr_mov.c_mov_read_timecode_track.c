#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  pb; } ;
struct TYPE_11__ {TYPE_1__* index_entries; int /*<<< orphan*/  nb_index_entries; TYPE_2__* priv_data; } ;
struct TYPE_10__ {int tmcd_flags; int /*<<< orphan*/  pb; } ;
struct TYPE_9__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AV_TIMECODE_FLAG_24HOURSMAX ; 
 int AV_TIMECODE_FLAG_ALLOWNEGATIVE ; 
 int AV_TIMECODE_FLAG_DROPFRAME ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_timecode_in_framenum_format (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mov_read_timecode_track(AVFormatContext *s, AVStream *st)
{
    MOVStreamContext *sc = st->priv_data;
    int flags = 0;
    int64_t cur_pos = avio_tell(sc->pb);
    uint32_t value;

    if (!st->nb_index_entries)
        return -1;

    avio_seek(sc->pb, st->index_entries->pos, SEEK_SET);
    value = avio_rb32(s->pb);

    if (sc->tmcd_flags & 0x0001) flags |= AV_TIMECODE_FLAG_DROPFRAME;
    if (sc->tmcd_flags & 0x0002) flags |= AV_TIMECODE_FLAG_24HOURSMAX;
    if (sc->tmcd_flags & 0x0004) flags |= AV_TIMECODE_FLAG_ALLOWNEGATIVE;

    /* Assume Counter flag is set to 1 in tmcd track (even though it is likely
     * not the case) and thus assume "frame number format" instead of QT one.
     * No sample with tmcd track can be found with a QT timecode at the moment,
     * despite what the tmcd track "suggests" (Counter flag set to 0 means QT
     * format). */
    parse_timecode_in_framenum_format(s, st, value, flags);

    avio_seek(sc->pb, cur_pos, SEEK_SET);
    return 0;
}