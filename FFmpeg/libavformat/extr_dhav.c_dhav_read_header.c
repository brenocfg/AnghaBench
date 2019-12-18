#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  signature ;
struct TYPE_13__ {scalar_t__ seekable; } ;
struct TYPE_12__ {int /*<<< orphan*/  ctx_flags; TYPE_3__* pb; TYPE_1__* priv_data; } ;
struct TYPE_11__ {int last_good_pos; int video_stream_index; int audio_stream_index; } ;
typedef  TYPE_1__ DHAVContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_read (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int avio_rl32 (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int avio_size (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_skip (TYPE_3__*,int) ; 
 void* avio_tell (TYPE_3__*) ; 
 int /*<<< orphan*/  ffio_ensure_seekback (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int dhav_read_header(AVFormatContext *s)
{
    DHAVContext *dhav = s->priv_data;
    uint8_t signature[5];

    ffio_ensure_seekback(s->pb, 5);
    avio_read(s->pb, signature, sizeof(signature));
    if (!memcmp(signature, "DAHUA", 5)) {
        avio_skip(s->pb, 0x400 - 5);
        dhav->last_good_pos = avio_tell(s->pb);
    } else {
        if (!memcmp(signature, "DHAV", 4)) {
            avio_seek(s->pb, -5, SEEK_CUR);
            dhav->last_good_pos = avio_tell(s->pb);
        } else if (s->pb->seekable) {
            avio_seek(s->pb, avio_size(s->pb) - 8, SEEK_SET);
            while (avio_rl32(s->pb) == MKTAG('d','h','a','v')) {
                int seek_back;

                seek_back = avio_rl32(s->pb) + 8;
                dhav->last_good_pos = avio_tell(s->pb);
                if (dhav->last_good_pos < seek_back)
                    break;
                avio_seek(s->pb, -seek_back, SEEK_CUR);
            }
        }
    }

    s->ctx_flags |= AVFMTCTX_NOHEADER;
    dhav->video_stream_index = -1;
    dhav->audio_stream_index = -1;

    return 0;
}