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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum InterpolateMethod { ____Placeholder_InterpolateMethod } InterpolateMethod ;
typedef  enum FillMethod { ____Placeholder_FillMethod } FillMethod ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
#define  FILL_CLAMP 133 
#define  FILL_MIRROR 132 
#define  FILL_ORIGINAL 131 
#define  INTERPOLATE_BILINEAR 130 
#define  INTERPOLATE_BIQUADRATIC 129 
#define  INTERPOLATE_NEAREST 128 
 int /*<<< orphan*/  av_assert2 (int) ; 
 float av_clipf (float,int /*<<< orphan*/ ,int) ; 
 float avpriv_mirror (float,int) ; 
 int /*<<< orphan*/  interpolate_bilinear (float,float,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interpolate_biquadratic (float,float,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interpolate_nearest (float,float,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ) ; 

int avfilter_transform(const uint8_t *src, uint8_t *dst,
                        int src_stride, int dst_stride,
                        int width, int height, const float *matrix,
                        enum InterpolateMethod interpolate,
                        enum FillMethod fill)
{
    int x, y;
    float x_s, y_s;
    uint8_t def = 0;
    uint8_t (*func)(float, float, const uint8_t *, int, int, int, uint8_t) = NULL;

    switch(interpolate) {
        case INTERPOLATE_NEAREST:
            func = interpolate_nearest;
            break;
        case INTERPOLATE_BILINEAR:
            func = interpolate_bilinear;
            break;
        case INTERPOLATE_BIQUADRATIC:
            func = interpolate_biquadratic;
            break;
        default:
            return AVERROR(EINVAL);
    }

    for (y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            x_s = x * matrix[0] + y * matrix[1] + matrix[2];
            y_s = x * matrix[3] + y * matrix[4] + matrix[5];

            switch(fill) {
                case FILL_ORIGINAL:
                    def = src[y * src_stride + x];
                    break;
                case FILL_CLAMP:
                    y_s = av_clipf(y_s, 0, height - 1);
                    x_s = av_clipf(x_s, 0, width - 1);
                    def = src[(int)y_s * src_stride + (int)x_s];
                    break;
                case FILL_MIRROR:
                    x_s = avpriv_mirror(x_s,  width-1);
                    y_s = avpriv_mirror(y_s, height-1);

                    av_assert2(x_s >= 0 && y_s >= 0);
                    av_assert2(x_s < width && y_s < height);
                    def = src[(int)y_s * src_stride + (int)x_s];
            }

            dst[y * dst_stride + x] = func(x_s, y_s, src, width, height, src_stride, def);
        }
    }
    return 0;
}