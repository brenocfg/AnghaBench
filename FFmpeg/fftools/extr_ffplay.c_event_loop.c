#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  double uint64_t ;
typedef  int int64_t ;
struct TYPE_29__ {double width; int force_refresh; int /*<<< orphan*/ * vis_texture; int /*<<< orphan*/  height; TYPE_6__* ic; scalar_t__ seek_pos; int /*<<< orphan*/  sampq; int /*<<< orphan*/  audio_stream; int /*<<< orphan*/  pictq; int /*<<< orphan*/  video_stream; int /*<<< orphan*/  vfilter_idx; int /*<<< orphan*/  show_mode; } ;
typedef  TYPE_7__ VideoState ;
struct TYPE_23__ {double data1; int /*<<< orphan*/  data2; int /*<<< orphan*/  event; } ;
struct TYPE_27__ {int state; double x; } ;
struct TYPE_26__ {double x; int /*<<< orphan*/  button; } ;
struct TYPE_24__ {int /*<<< orphan*/  sym; } ;
struct TYPE_25__ {TYPE_2__ keysym; } ;
struct TYPE_30__ {int type; TYPE_1__ window; TYPE_5__ motion; TYPE_4__ button; TYPE_3__ key; } ;
struct TYPE_28__ {int nb_chapters; double bit_rate; int start_time; double duration; int /*<<< orphan*/  pb; } ;
typedef  TYPE_8__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int AV_NOPTS_VALUE ; 
 double AV_TIME_BASE ; 
#define  FF_QUIT_EVENT 155 
#define  SDLK_0 154 
#define  SDLK_9 153 
#define  SDLK_DOWN 152 
 int /*<<< orphan*/  SDLK_ESCAPE ; 
#define  SDLK_KP_DIVIDE 151 
#define  SDLK_KP_MULTIPLY 150 
#define  SDLK_LEFT 149 
#define  SDLK_PAGEDOWN 148 
#define  SDLK_PAGEUP 147 
#define  SDLK_RIGHT 146 
#define  SDLK_SPACE 145 
#define  SDLK_UP 144 
#define  SDLK_a 143 
#define  SDLK_c 142 
#define  SDLK_f 141 
#define  SDLK_m 140 
#define  SDLK_p 139 
 int /*<<< orphan*/  SDLK_q ; 
#define  SDLK_s 138 
#define  SDLK_t 137 
#define  SDLK_v 136 
#define  SDLK_w 135 
 int /*<<< orphan*/  SDL_BUTTON_LEFT ; 
 int /*<<< orphan*/  SDL_BUTTON_RIGHT ; 
 int SDL_BUTTON_RMASK ; 
 int /*<<< orphan*/  SDL_DestroyTexture (int /*<<< orphan*/ *) ; 
#define  SDL_KEYDOWN 134 
#define  SDL_MOUSEBUTTONDOWN 133 
#define  SDL_MOUSEMOTION 132 
#define  SDL_QUIT 131 
 int /*<<< orphan*/  SDL_ShowCursor (int) ; 
 int /*<<< orphan*/  SDL_VOLUME_STEP ; 
#define  SDL_WINDOWEVENT 130 
#define  SDL_WINDOWEVENT_EXPOSED 129 
#define  SDL_WINDOWEVENT_SIZE_CHANGED 128 
 int /*<<< orphan*/  SHOW_MODE_VIDEO ; 
 int av_gettime_relative () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,double,int,int,int,int,int,int) ; 
 double avio_size (int /*<<< orphan*/ ) ; 
 double avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_hidden ; 
 int cursor_last_shown ; 
 int /*<<< orphan*/  do_exit (TYPE_7__*) ; 
 int /*<<< orphan*/  exit_on_keydown ; 
 int /*<<< orphan*/  exit_on_mousedown ; 
 double frame_queue_last_pos (int /*<<< orphan*/ *) ; 
 double get_master_clock (TYPE_7__*) ; 
 int /*<<< orphan*/  isnan (double) ; 
 int /*<<< orphan*/  nb_vfilters ; 
 int /*<<< orphan*/  refresh_loop_wait_event (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  screen_height ; 
 double screen_width ; 
 int /*<<< orphan*/  seek_by_bytes ; 
 int /*<<< orphan*/  seek_chapter (TYPE_7__*,int) ; 
 double seek_interval ; 
 int /*<<< orphan*/  step_to_next_frame (TYPE_7__*) ; 
 int /*<<< orphan*/  stream_cycle_channel (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_seek (TYPE_7__*,int,int,int) ; 
 int /*<<< orphan*/  toggle_audio_display (TYPE_7__*) ; 
 int /*<<< orphan*/  toggle_full_screen (TYPE_7__*) ; 
 int /*<<< orphan*/  toggle_mute (TYPE_7__*) ; 
 int /*<<< orphan*/  toggle_pause (TYPE_7__*) ; 
 int /*<<< orphan*/  update_volume (TYPE_7__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void event_loop(VideoState *cur_stream)
{
    SDL_Event event;
    double incr, pos, frac;

    for (;;) {
        double x;
        refresh_loop_wait_event(cur_stream, &event);
        switch (event.type) {
        case SDL_KEYDOWN:
            if (exit_on_keydown || event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {
                do_exit(cur_stream);
                break;
            }
            // If we don't yet have a window, skip all key events, because read_thread might still be initializing...
            if (!cur_stream->width)
                continue;
            switch (event.key.keysym.sym) {
            case SDLK_f:
                toggle_full_screen(cur_stream);
                cur_stream->force_refresh = 1;
                break;
            case SDLK_p:
            case SDLK_SPACE:
                toggle_pause(cur_stream);
                break;
            case SDLK_m:
                toggle_mute(cur_stream);
                break;
            case SDLK_KP_MULTIPLY:
            case SDLK_0:
                update_volume(cur_stream, 1, SDL_VOLUME_STEP);
                break;
            case SDLK_KP_DIVIDE:
            case SDLK_9:
                update_volume(cur_stream, -1, SDL_VOLUME_STEP);
                break;
            case SDLK_s: // S: Step to next frame
                step_to_next_frame(cur_stream);
                break;
            case SDLK_a:
                stream_cycle_channel(cur_stream, AVMEDIA_TYPE_AUDIO);
                break;
            case SDLK_v:
                stream_cycle_channel(cur_stream, AVMEDIA_TYPE_VIDEO);
                break;
            case SDLK_c:
                stream_cycle_channel(cur_stream, AVMEDIA_TYPE_VIDEO);
                stream_cycle_channel(cur_stream, AVMEDIA_TYPE_AUDIO);
                stream_cycle_channel(cur_stream, AVMEDIA_TYPE_SUBTITLE);
                break;
            case SDLK_t:
                stream_cycle_channel(cur_stream, AVMEDIA_TYPE_SUBTITLE);
                break;
            case SDLK_w:
#if CONFIG_AVFILTER
                if (cur_stream->show_mode == SHOW_MODE_VIDEO && cur_stream->vfilter_idx < nb_vfilters - 1) {
                    if (++cur_stream->vfilter_idx >= nb_vfilters)
                        cur_stream->vfilter_idx = 0;
                } else {
                    cur_stream->vfilter_idx = 0;
                    toggle_audio_display(cur_stream);
                }
#else
                toggle_audio_display(cur_stream);
#endif
                break;
            case SDLK_PAGEUP:
                if (cur_stream->ic->nb_chapters <= 1) {
                    incr = 600.0;
                    goto do_seek;
                }
                seek_chapter(cur_stream, 1);
                break;
            case SDLK_PAGEDOWN:
                if (cur_stream->ic->nb_chapters <= 1) {
                    incr = -600.0;
                    goto do_seek;
                }
                seek_chapter(cur_stream, -1);
                break;
            case SDLK_LEFT:
                incr = seek_interval ? -seek_interval : -10.0;
                goto do_seek;
            case SDLK_RIGHT:
                incr = seek_interval ? seek_interval : 10.0;
                goto do_seek;
            case SDLK_UP:
                incr = 60.0;
                goto do_seek;
            case SDLK_DOWN:
                incr = -60.0;
            do_seek:
                    if (seek_by_bytes) {
                        pos = -1;
                        if (pos < 0 && cur_stream->video_stream >= 0)
                            pos = frame_queue_last_pos(&cur_stream->pictq);
                        if (pos < 0 && cur_stream->audio_stream >= 0)
                            pos = frame_queue_last_pos(&cur_stream->sampq);
                        if (pos < 0)
                            pos = avio_tell(cur_stream->ic->pb);
                        if (cur_stream->ic->bit_rate)
                            incr *= cur_stream->ic->bit_rate / 8.0;
                        else
                            incr *= 180000.0;
                        pos += incr;
                        stream_seek(cur_stream, pos, incr, 1);
                    } else {
                        pos = get_master_clock(cur_stream);
                        if (isnan(pos))
                            pos = (double)cur_stream->seek_pos / AV_TIME_BASE;
                        pos += incr;
                        if (cur_stream->ic->start_time != AV_NOPTS_VALUE && pos < cur_stream->ic->start_time / (double)AV_TIME_BASE)
                            pos = cur_stream->ic->start_time / (double)AV_TIME_BASE;
                        stream_seek(cur_stream, (int64_t)(pos * AV_TIME_BASE), (int64_t)(incr * AV_TIME_BASE), 0);
                    }
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (exit_on_mousedown) {
                do_exit(cur_stream);
                break;
            }
            if (event.button.button == SDL_BUTTON_LEFT) {
                static int64_t last_mouse_left_click = 0;
                if (av_gettime_relative() - last_mouse_left_click <= 500000) {
                    toggle_full_screen(cur_stream);
                    cur_stream->force_refresh = 1;
                    last_mouse_left_click = 0;
                } else {
                    last_mouse_left_click = av_gettime_relative();
                }
            }
        case SDL_MOUSEMOTION:
            if (cursor_hidden) {
                SDL_ShowCursor(1);
                cursor_hidden = 0;
            }
            cursor_last_shown = av_gettime_relative();
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button != SDL_BUTTON_RIGHT)
                    break;
                x = event.button.x;
            } else {
                if (!(event.motion.state & SDL_BUTTON_RMASK))
                    break;
                x = event.motion.x;
            }
                if (seek_by_bytes || cur_stream->ic->duration <= 0) {
                    uint64_t size =  avio_size(cur_stream->ic->pb);
                    stream_seek(cur_stream, size*x/cur_stream->width, 0, 1);
                } else {
                    int64_t ts;
                    int ns, hh, mm, ss;
                    int tns, thh, tmm, tss;
                    tns  = cur_stream->ic->duration / 1000000LL;
                    thh  = tns / 3600;
                    tmm  = (tns % 3600) / 60;
                    tss  = (tns % 60);
                    frac = x / cur_stream->width;
                    ns   = frac * tns;
                    hh   = ns / 3600;
                    mm   = (ns % 3600) / 60;
                    ss   = (ns % 60);
                    av_log(NULL, AV_LOG_INFO,
                           "Seek to %2.0f%% (%2d:%02d:%02d) of total duration (%2d:%02d:%02d)       \n", frac*100,
                            hh, mm, ss, thh, tmm, tss);
                    ts = frac * cur_stream->ic->duration;
                    if (cur_stream->ic->start_time != AV_NOPTS_VALUE)
                        ts += cur_stream->ic->start_time;
                    stream_seek(cur_stream, ts, 0, 0);
                }
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    screen_width  = cur_stream->width  = event.window.data1;
                    screen_height = cur_stream->height = event.window.data2;
                    if (cur_stream->vis_texture) {
                        SDL_DestroyTexture(cur_stream->vis_texture);
                        cur_stream->vis_texture = NULL;
                    }
                case SDL_WINDOWEVENT_EXPOSED:
                    cur_stream->force_refresh = 1;
            }
            break;
        case SDL_QUIT:
        case FF_QUIT_EVENT:
            do_exit(cur_stream);
            break;
        default:
            break;
        }
    }
}