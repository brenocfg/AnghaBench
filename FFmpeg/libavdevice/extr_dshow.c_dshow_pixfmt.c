#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int DWORD ;

/* Variables and functions */
 int AV_PIX_FMT_0RGB32 ; 
 int AV_PIX_FMT_BGR24 ; 
 int AV_PIX_FMT_MONOWHITE ; 
 int AV_PIX_FMT_RGB4 ; 
 int AV_PIX_FMT_RGB555 ; 
 int AV_PIX_FMT_RGB8 ; 
#define  BI_BITFIELDS 129 
#define  BI_RGB 128 
 int avpriv_find_pix_fmt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_get_raw_pix_fmt_tags () ; 

__attribute__((used)) static enum AVPixelFormat dshow_pixfmt(DWORD biCompression, WORD biBitCount)
{
    switch(biCompression) {
    case BI_BITFIELDS:
    case BI_RGB:
        switch(biBitCount) { /* 1-8 are untested */
            case 1:
                return AV_PIX_FMT_MONOWHITE;
            case 4:
                return AV_PIX_FMT_RGB4;
            case 8:
                return AV_PIX_FMT_RGB8;
            case 16:
                return AV_PIX_FMT_RGB555;
            case 24:
                return AV_PIX_FMT_BGR24;
            case 32:
                return AV_PIX_FMT_0RGB32;
        }
    }
    return avpriv_find_pix_fmt(avpriv_get_raw_pix_fmt_tags(), biCompression); // all others
}