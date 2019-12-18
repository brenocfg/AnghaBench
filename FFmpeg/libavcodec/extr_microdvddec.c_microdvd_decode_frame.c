#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct microdvd_tag {int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int /*<<< orphan*/  str; scalar_t__ len; } ;
struct TYPE_18__ {TYPE_1__* priv_data; } ;
struct TYPE_17__ {char* data; int size; } ;
struct TYPE_16__ {scalar_t__ num_rects; } ;
struct TYPE_15__ {int /*<<< orphan*/  readorder; } ;
typedef  int /*<<< orphan*/  MICRODVD_TAGS ;
typedef  TYPE_1__ FFASSDecoderContext ;
typedef  TYPE_2__ AVSubtitle ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (TYPE_5__*,char,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_5__*,char*) ; 
 int ff_ass_add_rect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  microdvd_close_no_persistent_tags (TYPE_5__*,struct microdvd_tag*) ; 
 char* microdvd_load_tags (struct microdvd_tag*,char*) ; 
 int /*<<< orphan*/  microdvd_open_tags (TYPE_5__*,struct microdvd_tag*) ; 

__attribute__((used)) static int microdvd_decode_frame(AVCodecContext *avctx,
                                 void *data, int *got_sub_ptr, AVPacket *avpkt)
{
    AVSubtitle *sub = data;
    AVBPrint new_line;
    char *line = avpkt->data;
    char *end = avpkt->data + avpkt->size;
    FFASSDecoderContext *s = avctx->priv_data;
    struct microdvd_tag tags[sizeof(MICRODVD_TAGS) - 1] = {{0}};

    if (avpkt->size <= 0)
        return avpkt->size;

    av_bprint_init(&new_line, 0, 2048);

    // subtitle content
    while (line < end && *line) {

        // parse MicroDVD tags, and open them in ASS
        line = microdvd_load_tags(tags, line);
        microdvd_open_tags(&new_line, tags);

        // simple copy until EOL or forced carriage return
        while (line < end && *line && *line != '|') {
            av_bprint_chars(&new_line, *line, 1);
            line++;
        }

        // line split
        if (line < end && *line == '|') {
            microdvd_close_no_persistent_tags(&new_line, tags);
            av_bprintf(&new_line, "\\N");
            line++;
        }
    }
    if (new_line.len) {
        int ret = ff_ass_add_rect(sub, new_line.str, s->readorder++, 0, NULL, NULL);
        av_bprint_finalize(&new_line, NULL);
        if (ret < 0)
            return ret;
    }

    *got_sub_ptr = sub->num_rects > 0;
    return avpkt->size;
}