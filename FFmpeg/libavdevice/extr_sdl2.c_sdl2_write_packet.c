#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_23__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct TYPE_22__ {TYPE_1__** streams; TYPE_6__* priv_data; } ;
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int texture_fmt; int /*<<< orphan*/  renderer; int /*<<< orphan*/  texture_rect; int /*<<< orphan*/  texture; scalar_t__ enable_quit_action; int /*<<< orphan*/  window_height; int /*<<< orphan*/  window_width; } ;
struct TYPE_18__ {int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; int /*<<< orphan*/  event; } ;
struct TYPE_16__ {int /*<<< orphan*/  sym; } ;
struct TYPE_17__ {TYPE_2__ keysym; } ;
struct TYPE_19__ {int type; TYPE_4__ window; TYPE_3__ key; } ;
struct TYPE_15__ {TYPE_9__* codecpar; } ;
typedef  TYPE_5__ SDL_Event ;
typedef  TYPE_6__ SDLContext ;
typedef  TYPE_7__ AVPacket ;
typedef  TYPE_8__ AVFormatContext ;
typedef  TYPE_9__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  EIO ; 
#define  SDLK_ESCAPE 153 
#define  SDLK_q 152 
#define  SDL_KEYDOWN 151 
#define  SDL_PIXELFORMAT_ABGR8888 150 
#define  SDL_PIXELFORMAT_ARGB8888 149 
#define  SDL_PIXELFORMAT_BGR24 148 
#define  SDL_PIXELFORMAT_BGR555 147 
#define  SDL_PIXELFORMAT_BGR565 146 
#define  SDL_PIXELFORMAT_BGR888 145 
#define  SDL_PIXELFORMAT_BGRA8888 144 
#define  SDL_PIXELFORMAT_BGRX8888 143 
#define  SDL_PIXELFORMAT_IYUV 142 
#define  SDL_PIXELFORMAT_RGB24 141 
#define  SDL_PIXELFORMAT_RGB332 140 
#define  SDL_PIXELFORMAT_RGB444 139 
#define  SDL_PIXELFORMAT_RGB555 138 
#define  SDL_PIXELFORMAT_RGB565 137 
#define  SDL_PIXELFORMAT_RGB888 136 
#define  SDL_PIXELFORMAT_RGBA8888 135 
#define  SDL_PIXELFORMAT_RGBX8888 134 
#define  SDL_PIXELFORMAT_UYVY 133 
#define  SDL_PIXELFORMAT_YUY2 132 
 scalar_t__ SDL_PollEvent (TYPE_5__*) ; 
#define  SDL_QUIT 131 
 int /*<<< orphan*/  SDL_RenderClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RenderCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_RenderPresent (int /*<<< orphan*/ ) ; 
 int SDL_UpdateTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int SDL_UpdateYUVTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
#define  SDL_WINDOWEVENT 130 
#define  SDL_WINDOWEVENT_RESIZED 129 
#define  SDL_WINDOWEVENT_SIZE_CHANGED 128 
 int /*<<< orphan*/  av_image_fill_arrays (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  compute_texture_rect (TYPE_8__*) ; 
 int /*<<< orphan*/  sdl2_write_trailer (TYPE_8__*) ; 

__attribute__((used)) static int sdl2_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret, quit = 0;
    SDLContext *sdl = s->priv_data;
    AVCodecParameters *codecpar = s->streams[0]->codecpar;
    uint8_t *data[4];
    int linesize[4];

    SDL_Event event;
    if (SDL_PollEvent(&event)){
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_q:
                quit = 1;
                break;
            default:
                break;
            }
            break;
        case SDL_QUIT:
            quit = 1;
            break;
        case SDL_WINDOWEVENT:
            switch(event.window.event){
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                sdl->window_width  = event.window.data1;
                sdl->window_height = event.window.data2;
                compute_texture_rect(s);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    if (quit && sdl->enable_quit_action) {
        sdl2_write_trailer(s);
        return AVERROR(EIO);
    }

    av_image_fill_arrays(data, linesize, pkt->data, codecpar->format, codecpar->width, codecpar->height, 1);
    switch (sdl->texture_fmt) {
    /* case SDL_PIXELFORMAT_ARGB4444:
     * case SDL_PIXELFORMAT_RGBA4444:
     * case SDL_PIXELFORMAT_ABGR4444:
     * case SDL_PIXELFORMAT_BGRA4444:
     * case SDL_PIXELFORMAT_ARGB1555:
     * case SDL_PIXELFORMAT_RGBA5551:
     * case SDL_PIXELFORMAT_ABGR1555:
     * case SDL_PIXELFORMAT_BGRA5551:
     * case SDL_PIXELFORMAT_ARGB2101010:
     */
    case SDL_PIXELFORMAT_IYUV:
    case SDL_PIXELFORMAT_YUY2:
    case SDL_PIXELFORMAT_UYVY:
        ret = SDL_UpdateYUVTexture(sdl->texture, NULL,
                                   data[0], linesize[0],
                                   data[1], linesize[1],
                                   data[2], linesize[2]);
        break;
    case SDL_PIXELFORMAT_RGB332:
    case SDL_PIXELFORMAT_RGB444:
    case SDL_PIXELFORMAT_RGB555:
    case SDL_PIXELFORMAT_BGR555:
    case SDL_PIXELFORMAT_RGB565:
    case SDL_PIXELFORMAT_BGR565:
    case SDL_PIXELFORMAT_RGB24:
    case SDL_PIXELFORMAT_BGR24:
    case SDL_PIXELFORMAT_RGB888:
    case SDL_PIXELFORMAT_RGBX8888:
    case SDL_PIXELFORMAT_BGR888:
    case SDL_PIXELFORMAT_BGRX8888:
    case SDL_PIXELFORMAT_ARGB8888:
    case SDL_PIXELFORMAT_RGBA8888:
    case SDL_PIXELFORMAT_ABGR8888:
    case SDL_PIXELFORMAT_BGRA8888:
        ret = SDL_UpdateTexture(sdl->texture, NULL, data[0], linesize[0]);
        break;
    default:
        av_log(NULL, AV_LOG_FATAL, "Unsupported pixel format\n");
        ret = -1;
        break;
    }
    SDL_RenderClear(sdl->renderer);
    SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, &sdl->texture_rect);
    SDL_RenderPresent(sdl->renderer);
    return ret;
}