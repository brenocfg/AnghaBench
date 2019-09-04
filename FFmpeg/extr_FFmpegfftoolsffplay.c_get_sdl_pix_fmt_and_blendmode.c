#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Uint32 ;
struct TYPE_3__ {int format; int /*<<< orphan*/  texture_fmt; } ;
typedef  int /*<<< orphan*/  SDL_BlendMode ;

/* Variables and functions */
 int AV_PIX_FMT_BGR32 ; 
 int AV_PIX_FMT_BGR32_1 ; 
 int AV_PIX_FMT_RGB32 ; 
 int AV_PIX_FMT_RGB32_1 ; 
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_BLENDMODE_BLEND ; 
 int /*<<< orphan*/  SDL_BLENDMODE_NONE ; 
 int /*<<< orphan*/  SDL_PIXELFORMAT_UNKNOWN ; 
 TYPE_1__* sdl_texture_format_map ; 

__attribute__((used)) static void get_sdl_pix_fmt_and_blendmode(int format, Uint32 *sdl_pix_fmt, SDL_BlendMode *sdl_blendmode)
{
    int i;
    *sdl_blendmode = SDL_BLENDMODE_NONE;
    *sdl_pix_fmt = SDL_PIXELFORMAT_UNKNOWN;
    if (format == AV_PIX_FMT_RGB32   ||
        format == AV_PIX_FMT_RGB32_1 ||
        format == AV_PIX_FMT_BGR32   ||
        format == AV_PIX_FMT_BGR32_1)
        *sdl_blendmode = SDL_BLENDMODE_BLEND;
    for (i = 0; i < FF_ARRAY_ELEMS(sdl_texture_format_map) - 1; i++) {
        if (format == sdl_texture_format_map[i].format) {
            *sdl_pix_fmt = sdl_texture_format_map[i].texture_fmt;
            return;
        }
    }
}