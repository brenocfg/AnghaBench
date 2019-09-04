#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int flags; } ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVFMT_FLAG_BITEXACT ; 
 int /*<<< orphan*/  LIBAVFORMAT_IDENT ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_write_covr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mov_write_int8_metadata (TYPE_1__*,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  mov_write_string_metadata (TYPE_1__*,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  mov_write_string_tag (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mov_write_tmpo_tag (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mov_write_trkn_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_ilst_tag(AVIOContext *pb, MOVMuxContext *mov,
                              AVFormatContext *s)
{
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "ilst");
    mov_write_string_metadata(s, pb, "\251nam", "title"    , 1);
    mov_write_string_metadata(s, pb, "\251ART", "artist"   , 1);
    mov_write_string_metadata(s, pb, "aART", "album_artist", 1);
    mov_write_string_metadata(s, pb, "\251wrt", "composer" , 1);
    mov_write_string_metadata(s, pb, "\251alb", "album"    , 1);
    mov_write_string_metadata(s, pb, "\251day", "date"     , 1);
    if (!mov_write_string_metadata(s, pb, "\251too", "encoding_tool", 1)) {
        if (!(s->flags & AVFMT_FLAG_BITEXACT))
            mov_write_string_tag(pb, "\251too", LIBAVFORMAT_IDENT, 0, 1);
    }
    mov_write_string_metadata(s, pb, "\251cmt", "comment"  , 1);
    mov_write_string_metadata(s, pb, "\251gen", "genre"    , 1);
    mov_write_string_metadata(s, pb, "cprt",    "copyright", 1);
    mov_write_string_metadata(s, pb, "\251grp", "grouping" , 1);
    mov_write_string_metadata(s, pb, "\251lyr", "lyrics"   , 1);
    mov_write_string_metadata(s, pb, "desc",    "description",1);
    mov_write_string_metadata(s, pb, "ldes",    "synopsis" , 1);
    mov_write_string_metadata(s, pb, "tvsh",    "show"     , 1);
    mov_write_string_metadata(s, pb, "tven",    "episode_id",1);
    mov_write_string_metadata(s, pb, "tvnn",    "network"  , 1);
    mov_write_string_metadata(s, pb, "keyw",    "keywords"  , 1);
    mov_write_int8_metadata  (s, pb, "tves",    "episode_sort",4);
    mov_write_int8_metadata  (s, pb, "tvsn",    "season_number",4);
    mov_write_int8_metadata  (s, pb, "stik",    "media_type",1);
    mov_write_int8_metadata  (s, pb, "hdvd",    "hd_video",  1);
    mov_write_int8_metadata  (s, pb, "pgap",    "gapless_playback",1);
    mov_write_int8_metadata  (s, pb, "cpil",    "compilation", 1);
    mov_write_covr(pb, s);
    mov_write_trkn_tag(pb, mov, s, 0); // track number
    mov_write_trkn_tag(pb, mov, s, 1); // disc number
    mov_write_tmpo_tag(pb, s);
    return update_size(pb, pos);
}