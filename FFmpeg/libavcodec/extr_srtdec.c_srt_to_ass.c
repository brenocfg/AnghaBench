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
typedef  int const int64_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 scalar_t__ ASS_DEFAULT_PLAYRESX ; 
 scalar_t__ ASS_DEFAULT_PLAYRESY ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,int const,int const) ; 
 int ff_htmlmarkup_to_ass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int srt_to_ass(AVCodecContext *avctx, AVBPrint *dst,
                       const char *in, int x1, int y1, int x2, int y2)
{
    if (x1 >= 0 && y1 >= 0) {
        /* XXX: here we rescale coordinate assuming they are in DVD resolution
         * (720x480) since we don't have anything better */

        if (x2 >= 0 && y2 >= 0 && (x2 != x1 || y2 != y1) && x2 >= x1 && y2 >= y1) {
            /* text rectangle defined, write the text at the center of the rectangle */
            const int cx = x1 + (x2 - x1)/2;
            const int cy = y1 + (y2 - y1)/2;
            const int scaled_x = cx * (int64_t)ASS_DEFAULT_PLAYRESX / 720;
            const int scaled_y = cy * (int64_t)ASS_DEFAULT_PLAYRESY / 480;
            av_bprintf(dst, "{\\an5}{\\pos(%d,%d)}", scaled_x, scaled_y);
        } else {
            /* only the top left corner, assume the text starts in that corner */
            const int scaled_x = x1 * (int64_t)ASS_DEFAULT_PLAYRESX / 720;
            const int scaled_y = y1 * (int64_t)ASS_DEFAULT_PLAYRESY / 480;
            av_bprintf(dst, "{\\an1}{\\pos(%d,%d)}", scaled_x, scaled_y);
        }
    }

    return ff_htmlmarkup_to_ass(avctx, dst, in);
}