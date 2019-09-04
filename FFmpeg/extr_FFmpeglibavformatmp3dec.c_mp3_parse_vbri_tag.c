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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {void* frames; void* header_filesize; } ;
typedef  TYPE_1__ MP3DecContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int avio_rb16 (int /*<<< orphan*/ ) ; 
 void* avio_rb32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mp3_parse_vbri_tag(AVFormatContext *s, AVStream *st, int64_t base)
{
    uint32_t v;
    MP3DecContext *mp3 = s->priv_data;

    /* Check for VBRI tag (always 32 bytes after end of mpegaudio header) */
    avio_seek(s->pb, base + 4 + 32, SEEK_SET);
    v = avio_rb32(s->pb);
    if (v == MKBETAG('V', 'B', 'R', 'I')) {
        /* Check tag version */
        if (avio_rb16(s->pb) == 1) {
            /* skip delay and quality */
            avio_skip(s->pb, 4);
            mp3->header_filesize = avio_rb32(s->pb);
            mp3->frames = avio_rb32(s->pb);
        }
    }
}