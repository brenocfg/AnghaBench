#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct AVFormatContext {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_2__ {scalar_t__ xing_offset; scalar_t__ write_id3v1; scalar_t__ pics_to_write; } ;
typedef  TYPE_1__ MP3Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int ID3v1_TAG_SIZE ; 
 int /*<<< orphan*/  av_log (struct AVFormatContext*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ id3v1_create_tag (struct AVFormatContext*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp3_queue_flush (struct AVFormatContext*) ; 
 int /*<<< orphan*/  mp3_update_xing (struct AVFormatContext*) ; 

__attribute__((used)) static int mp3_write_trailer(struct AVFormatContext *s)
{
    uint8_t buf[ID3v1_TAG_SIZE];
    MP3Context *mp3 = s->priv_data;

    if (mp3->pics_to_write) {
        av_log(s, AV_LOG_WARNING, "No packets were sent for some of the "
               "attached pictures.\n");
        mp3_queue_flush(s);
    }

    /* write the id3v1 tag */
    if (mp3->write_id3v1 && id3v1_create_tag(s, buf) > 0) {
        avio_write(s->pb, buf, ID3v1_TAG_SIZE);
    }

    if (mp3->xing_offset)
        mp3_update_xing(s);

    return 0;
}