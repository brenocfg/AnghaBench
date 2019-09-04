#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int color_space; } ;
typedef  TYPE_1__ opj_image_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int FF_ARRAY_ELEMS (int*) ; 
#define  OPJ_CLRSPC_GRAY 130 
#define  OPJ_CLRSPC_SRGB 129 
#define  OPJ_CLRSPC_SYCC 128 
 int* libopenjpeg_all_pix_fmts ; 
 int* libopenjpeg_gray_pix_fmts ; 
 scalar_t__ libopenjpeg_matches_pix_fmt (TYPE_1__ const*,int const) ; 
 int* libopenjpeg_rgb_pix_fmts ; 
 int* libopenjpeg_yuv_pix_fmts ; 

__attribute__((used)) static inline enum AVPixelFormat libopenjpeg_guess_pix_fmt(const opj_image_t *image) {
    int index;
    const enum AVPixelFormat *possible_fmts = NULL;
    int possible_fmts_nb = 0;

    switch (image->color_space) {
    case OPJ_CLRSPC_SRGB:
        possible_fmts    = libopenjpeg_rgb_pix_fmts;
        possible_fmts_nb = FF_ARRAY_ELEMS(libopenjpeg_rgb_pix_fmts);
        break;
    case OPJ_CLRSPC_GRAY:
        possible_fmts    = libopenjpeg_gray_pix_fmts;
        possible_fmts_nb = FF_ARRAY_ELEMS(libopenjpeg_gray_pix_fmts);
        break;
    case OPJ_CLRSPC_SYCC:
        possible_fmts    = libopenjpeg_yuv_pix_fmts;
        possible_fmts_nb = FF_ARRAY_ELEMS(libopenjpeg_yuv_pix_fmts);
        break;
    default:
        possible_fmts    = libopenjpeg_all_pix_fmts;
        possible_fmts_nb = FF_ARRAY_ELEMS(libopenjpeg_all_pix_fmts);
        break;
    }

    for (index = 0; index < possible_fmts_nb; ++index)
        if (libopenjpeg_matches_pix_fmt(image, possible_fmts[index])) {
            return possible_fmts[index];
        }

    return AV_PIX_FMT_NONE;
}