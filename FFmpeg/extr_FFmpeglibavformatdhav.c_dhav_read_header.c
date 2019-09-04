#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  signature ;
struct TYPE_5__ {int /*<<< orphan*/  ctx_flags; int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int video_stream_index; int audio_stream_index; } ;
typedef  TYPE_1__ DHAVContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffio_ensure_seekback (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int dhav_read_header(AVFormatContext *s)
{
    DHAVContext *dhav = s->priv_data;
    uint8_t signature[5];

    ffio_ensure_seekback(s->pb, 5);
    avio_read(s->pb, signature, sizeof(signature));
    if (!memcmp(signature, "DAHUA", 5))
        avio_skip(s->pb, 0x400 - 5);
    else
        avio_seek(s->pb, -5, SEEK_CUR);

    s->ctx_flags |= AVFMTCTX_NOHEADER;
    dhav->video_stream_index = -1;
    dhav->audio_stream_index = -1;

    return 0;
}