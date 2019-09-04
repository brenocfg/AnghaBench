#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int height; int /*<<< orphan*/  color_range; int /*<<< orphan*/  pix_fmt; } ;
typedef  int /*<<< orphan*/ * CFNumberRef ;
typedef  int /*<<< orphan*/ * CFMutableDictionaryRef ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CFDictionaryCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFDictionarySetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFNumberCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  add_color_attr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int get_cv_pixel_format (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFCopyStringDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFNumberSInt32Type ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 
 int /*<<< orphan*/  kCVPixelBufferHeightKey ; 
 int /*<<< orphan*/  kCVPixelBufferPixelFormatTypeKey ; 
 int /*<<< orphan*/  kCVPixelBufferWidthKey ; 
 int /*<<< orphan*/  vt_release_num (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int create_cv_pixel_buffer_info(AVCodecContext* avctx,
                                       CFMutableDictionaryRef* dict)
{
    CFNumberRef cv_color_format_num = NULL;
    CFNumberRef width_num = NULL;
    CFNumberRef height_num = NULL;
    CFMutableDictionaryRef pixel_buffer_info = NULL;
    int cv_color_format;
    int status = get_cv_pixel_format(avctx,
                                     avctx->pix_fmt,
                                     avctx->color_range,
                                     &cv_color_format,
                                     NULL);
    if (status) return status;

    pixel_buffer_info = CFDictionaryCreateMutable(
                            kCFAllocatorDefault,
                            20,
                            &kCFCopyStringDictionaryKeyCallBacks,
                            &kCFTypeDictionaryValueCallBacks);

    if (!pixel_buffer_info) goto pbinfo_nomem;

    cv_color_format_num = CFNumberCreate(kCFAllocatorDefault,
                                         kCFNumberSInt32Type,
                                         &cv_color_format);
    if (!cv_color_format_num) goto pbinfo_nomem;

    CFDictionarySetValue(pixel_buffer_info,
                         kCVPixelBufferPixelFormatTypeKey,
                         cv_color_format_num);
    vt_release_num(&cv_color_format_num);

    width_num = CFNumberCreate(kCFAllocatorDefault,
                               kCFNumberSInt32Type,
                               &avctx->width);
    if (!width_num) return AVERROR(ENOMEM);

    CFDictionarySetValue(pixel_buffer_info,
                         kCVPixelBufferWidthKey,
                         width_num);
    vt_release_num(&width_num);

    height_num = CFNumberCreate(kCFAllocatorDefault,
                                kCFNumberSInt32Type,
                                &avctx->height);
    if (!height_num) goto pbinfo_nomem;

    CFDictionarySetValue(pixel_buffer_info,
                         kCVPixelBufferHeightKey,
                         height_num);
    vt_release_num(&height_num);

    add_color_attr(avctx, pixel_buffer_info);

    *dict = pixel_buffer_info;
    return 0;

pbinfo_nomem:
    vt_release_num(&cv_color_format_num);
    vt_release_num(&width_num);
    vt_release_num(&height_num);
    if (pixel_buffer_info) CFRelease(pixel_buffer_info);

    return AVERROR(ENOMEM);
}