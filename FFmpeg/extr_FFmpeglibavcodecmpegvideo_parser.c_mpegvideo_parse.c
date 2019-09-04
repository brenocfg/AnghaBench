#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct MpvParseContext {int /*<<< orphan*/  pc; } ;
struct TYPE_9__ {int /*<<< orphan*/  framerate; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  repeat_pict; int /*<<< orphan*/  pict_type; struct MpvParseContext* priv_data; } ;
typedef  int /*<<< orphan*/  ParseContext ;
typedef  TYPE_1__ AVCodecParserContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int PARSER_FLAG_COMPLETE_FRAMES ; 
 int /*<<< orphan*/  av_q2d (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_combine_frame (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int*) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_mpeg1_find_frame_end (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  mpegvideo_extract_headers (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int mpegvideo_parse(AVCodecParserContext *s,
                           AVCodecContext *avctx,
                           const uint8_t **poutbuf, int *poutbuf_size,
                           const uint8_t *buf, int buf_size)
{
    struct MpvParseContext *pc1 = s->priv_data;
    ParseContext *pc= &pc1->pc;
    int next;

    if(s->flags & PARSER_FLAG_COMPLETE_FRAMES){
        next= buf_size;
    }else{
        next= ff_mpeg1_find_frame_end(pc, buf, buf_size, s);

        if (ff_combine_frame(pc, next, &buf, &buf_size) < 0) {
            *poutbuf = NULL;
            *poutbuf_size = 0;
            return buf_size;
        }

    }
    /* we have a full frame : we just parse the first few MPEG headers
       to have the full timing information. The time take by this
       function should be negligible for uncorrupted streams */
    mpegvideo_extract_headers(s, avctx, buf, buf_size);
    ff_dlog(NULL, "pict_type=%d frame_rate=%0.3f repeat_pict=%d\n",
            s->pict_type, av_q2d(avctx->framerate), s->repeat_pict);

    *poutbuf = buf;
    *poutbuf_size = buf_size;
    return next;
}