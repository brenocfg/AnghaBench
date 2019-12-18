#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  char const uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_17__ {int* linesize; int palette_has_changed; scalar_t__* data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_16__ {int height; int /*<<< orphan*/  width; int /*<<< orphan*/  frame_number; TYPE_1__* priv_data; } ;
struct TYPE_15__ {char* data; int size; } ;
struct TYPE_14__ {int first_frame; int state; int x; size_t nb_args; int* args; TYPE_6__* frame; } ;
typedef  TYPE_1__ AnsiContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FONT_WIDTH ; 
 size_t MAX_NB_ARGS ; 
#define  STATE_CODE 131 
#define  STATE_ESCAPE 130 
#define  STATE_MUSIC_PREAMBLE 129 
#define  STATE_NORMAL 128 
 int av_frame_ref (void*,TYPE_6__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  draw_char (TYPE_3__*,char const) ; 
 int /*<<< orphan*/  erase_screen (TYPE_3__*) ; 
 int execute_code (TYPE_3__*,char const) ; 
 int ff_reget_buffer (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hscroll (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_palette (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    AnsiContext *s = avctx->priv_data;
    uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    const uint8_t *buf_end   = buf+buf_size;
    int ret, i, count;

    if ((ret = ff_reget_buffer(avctx, s->frame, 0)) < 0)
        return ret;
    if (!avctx->frame_number) {
        for (i=0; i<avctx->height; i++)
            memset(s->frame->data[0]+ i*s->frame->linesize[0], 0, avctx->width);
        memset(s->frame->data[1], 0, AVPALETTE_SIZE);
    }

    s->frame->pict_type           = AV_PICTURE_TYPE_I;
    s->frame->palette_has_changed = 1;
    set_palette((uint32_t *)s->frame->data[1]);
    if (!s->first_frame) {
        erase_screen(avctx);
        s->first_frame = 1;
    }

    while(buf < buf_end) {
        switch(s->state) {
        case STATE_NORMAL:
            switch (buf[0]) {
            case 0x00: //NUL
            case 0x07: //BEL
            case 0x1A: //SUB
                /* ignore */
                break;
            case 0x08: //BS
                s->x = FFMAX(s->x - 1, 0);
                break;
            case 0x09: //HT
                i = s->x / FONT_WIDTH;
                count = ((i + 8) & ~7) - i;
                for (i = 0; i < count; i++)
                    draw_char(avctx, ' ');
                break;
            case 0x0A: //LF
                hscroll(avctx);
            case 0x0D: //CR
                s->x = 0;
                break;
            case 0x0C: //FF
                erase_screen(avctx);
                break;
            case 0x1B: //ESC
                s->state = STATE_ESCAPE;
                break;
            default:
                draw_char(avctx, buf[0]);
            }
            break;
        case STATE_ESCAPE:
            if (buf[0] == '[') {
                s->state   = STATE_CODE;
                s->nb_args = 0;
                s->args[0] = -1;
            } else {
                s->state = STATE_NORMAL;
                draw_char(avctx, 0x1B);
                continue;
            }
            break;
        case STATE_CODE:
            switch(buf[0]) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                if (s->nb_args < MAX_NB_ARGS && s->args[s->nb_args] < 6553)
                    s->args[s->nb_args] = FFMAX(s->args[s->nb_args], 0) * 10 + buf[0] - '0';
                break;
            case ';':
                s->nb_args++;
                if (s->nb_args < MAX_NB_ARGS)
                    s->args[s->nb_args] = 0;
                break;
            case 'M':
                s->state = STATE_MUSIC_PREAMBLE;
                break;
            case '=': case '?':
                /* ignore */
                break;
            default:
                if (s->nb_args > MAX_NB_ARGS)
                    av_log(avctx, AV_LOG_WARNING, "args overflow (%i)\n", s->nb_args);
                if (s->nb_args < MAX_NB_ARGS && s->args[s->nb_args] >= 0)
                    s->nb_args++;
                if ((ret = execute_code(avctx, buf[0])) < 0)
                    return ret;
                s->state = STATE_NORMAL;
            }
            break;
        case STATE_MUSIC_PREAMBLE:
            if (buf[0] == 0x0E || buf[0] == 0x1B)
                s->state = STATE_NORMAL;
            /* ignore music data */
            break;
        }
        buf++;
    }

    *got_frame = 1;
    if ((ret = av_frame_ref(data, s->frame)) < 0)
        return ret;
    return buf_size;
}