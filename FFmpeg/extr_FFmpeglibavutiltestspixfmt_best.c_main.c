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

/* Variables and functions */
 int AV_PIX_FMT_0RGB ; 
 int AV_PIX_FMT_ABGR ; 
 int AV_PIX_FMT_AYUV64 ; 
 int AV_PIX_FMT_BGR24 ; 
 int AV_PIX_FMT_BGR4 ; 
 int AV_PIX_FMT_BGR565 ; 
 int AV_PIX_FMT_BGRA64 ; 
 int AV_PIX_FMT_DXVA2_VLD ; 
 int AV_PIX_FMT_GBRAP ; 
 int AV_PIX_FMT_GBRAP10 ; 
 int AV_PIX_FMT_GBRAP12 ; 
 int AV_PIX_FMT_GBRAP16 ; 
 int AV_PIX_FMT_GBRP ; 
 int AV_PIX_FMT_GBRP10 ; 
 int AV_PIX_FMT_GBRP16 ; 
 int AV_PIX_FMT_GRAY10 ; 
 int AV_PIX_FMT_GRAY10BE ; 
 int AV_PIX_FMT_GRAY10LE ; 
 int AV_PIX_FMT_GRAY12 ; 
 int AV_PIX_FMT_GRAY16 ; 
 int AV_PIX_FMT_GRAY16BE ; 
 int AV_PIX_FMT_GRAY16LE ; 
 int AV_PIX_FMT_GRAY8 ; 
 int AV_PIX_FMT_MONOBLACK ; 
 int AV_PIX_FMT_MONOWHITE ; 
 int AV_PIX_FMT_NV12 ; 
 int AV_PIX_FMT_NV16 ; 
 int AV_PIX_FMT_P010 ; 
 int AV_PIX_FMT_P016 ; 
 int AV_PIX_FMT_RGB24 ; 
 int AV_PIX_FMT_RGB444 ; 
 int AV_PIX_FMT_RGB48 ; 
 int AV_PIX_FMT_RGB48BE ; 
 int AV_PIX_FMT_RGB48LE ; 
 int AV_PIX_FMT_RGB555 ; 
 int AV_PIX_FMT_RGB565 ; 
 int AV_PIX_FMT_RGB565BE ; 
 int AV_PIX_FMT_RGB565LE ; 
 int AV_PIX_FMT_RGBA ; 
 int AV_PIX_FMT_RGBA64 ; 
 int AV_PIX_FMT_UYVY422 ; 
 int AV_PIX_FMT_UYYVYY411 ; 
 int AV_PIX_FMT_VDPAU ; 
 int AV_PIX_FMT_YA16 ; 
 int AV_PIX_FMT_YA8 ; 
 int AV_PIX_FMT_YUV410P ; 
 int AV_PIX_FMT_YUV411P ; 
 int AV_PIX_FMT_YUV420P ; 
 int AV_PIX_FMT_YUV420P10 ; 
 int AV_PIX_FMT_YUV420P12 ; 
 int AV_PIX_FMT_YUV420P16 ; 
 int AV_PIX_FMT_YUV420P9 ; 
 int AV_PIX_FMT_YUV422P ; 
 int AV_PIX_FMT_YUV422P10 ; 
 int AV_PIX_FMT_YUV422P10BE ; 
 int AV_PIX_FMT_YUV422P10LE ; 
 int AV_PIX_FMT_YUV440P ; 
 int AV_PIX_FMT_YUV440P10 ; 
 int AV_PIX_FMT_YUV440P12 ; 
 int AV_PIX_FMT_YUV444P ; 
 int AV_PIX_FMT_YUV444P10 ; 
 int AV_PIX_FMT_YUV444P12 ; 
 int AV_PIX_FMT_YUV444P16 ; 
 int AV_PIX_FMT_YUV444P16BE ; 
 int AV_PIX_FMT_YUV444P16LE ; 
 int AV_PIX_FMT_YUV444P9 ; 
 int AV_PIX_FMT_YUVA420P ; 
 int AV_PIX_FMT_YUVA422P ; 
 int AV_PIX_FMT_YUVA444P ; 
 int AV_PIX_FMT_YUYV422 ; 
 int FF_ARRAY_ELEMS (int*) ; 
 char* av_get_pix_fmt_name (int) ; 
 int find_best (int) ; 
 int* pixfmt_list ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(void)
{
    enum AVPixelFormat output;
    int i, pass = 0, fail = 0;

#define TEST(input, expected) do {                              \
        output = find_best(input);                              \
        if (output != expected) {                               \
            printf("Matching %s: got %s, expected %s\n",        \
                   av_get_pix_fmt_name(input),                  \
                   av_get_pix_fmt_name(output),                 \
                   av_get_pix_fmt_name(expected));              \
            ++fail;                                             \
        } else                                                  \
            ++pass;                                             \
    } while (0)

    // Same formats.
    for (i = 0; i < FF_ARRAY_ELEMS(pixfmt_list); i++)
        TEST(pixfmt_list[i], pixfmt_list[i]);

    // Formats containing the same data in different layouts.
    TEST(AV_PIX_FMT_MONOBLACK, AV_PIX_FMT_MONOWHITE);
    TEST(AV_PIX_FMT_NV12,      AV_PIX_FMT_YUV420P);
    TEST(AV_PIX_FMT_P010,      AV_PIX_FMT_YUV420P10);
    TEST(AV_PIX_FMT_P016,      AV_PIX_FMT_YUV420P16);
    TEST(AV_PIX_FMT_NV16,      AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_YUYV422,   AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_UYVY422,   AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_BGR565,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_BGR24,     AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_GBRP,      AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_0RGB,      AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_GBRP16,    AV_PIX_FMT_RGB48);

    // Formats additionally containing alpha (here ignored).
    TEST(AV_PIX_FMT_YA8,       AV_PIX_FMT_GRAY8);
    TEST(AV_PIX_FMT_YA16,      AV_PIX_FMT_GRAY16);
    TEST(AV_PIX_FMT_YUVA420P,  AV_PIX_FMT_YUV420P);
    TEST(AV_PIX_FMT_YUVA422P,  AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_YUVA444P,  AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_AYUV64,    AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_RGBA,      AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_ABGR,      AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_GBRAP,     AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_RGBA64,    AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_BGRA64,    AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_GBRAP16,   AV_PIX_FMT_RGB48);

    // Formats requiring upsampling to represent exactly.
    TEST(AV_PIX_FMT_GRAY12,    AV_PIX_FMT_GRAY16);
    TEST(AV_PIX_FMT_YUV410P,   AV_PIX_FMT_YUV420P);
    TEST(AV_PIX_FMT_YUV411P,   AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_UYYVYY411, AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_YUV440P,   AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_YUV440P10, AV_PIX_FMT_YUV444P10);
    TEST(AV_PIX_FMT_YUV440P12, AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_YUV420P9,  AV_PIX_FMT_YUV420P10);
    TEST(AV_PIX_FMT_YUV420P12, AV_PIX_FMT_YUV420P16);
    TEST(AV_PIX_FMT_YUV444P9,  AV_PIX_FMT_YUV444P10);
    TEST(AV_PIX_FMT_YUV444P12, AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_BGR4,      AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_RGB444,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_RGB555,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_GBRP10,    AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_GBRAP10,   AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_GBRAP12,   AV_PIX_FMT_RGB48);

    // Formats containing the same data in different endianness.
    TEST(AV_PIX_FMT_GRAY10BE,    AV_PIX_FMT_GRAY10);
    TEST(AV_PIX_FMT_GRAY10LE,    AV_PIX_FMT_GRAY10);
    TEST(AV_PIX_FMT_GRAY16BE,    AV_PIX_FMT_GRAY16);
    TEST(AV_PIX_FMT_GRAY16LE,    AV_PIX_FMT_GRAY16);
    TEST(AV_PIX_FMT_YUV422P10BE, AV_PIX_FMT_YUV422P10);
    TEST(AV_PIX_FMT_YUV422P10LE, AV_PIX_FMT_YUV422P10);
    TEST(AV_PIX_FMT_YUV444P16BE, AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_YUV444P16LE, AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_RGB565BE,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_RGB565LE,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_RGB48BE,     AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_RGB48LE,     AV_PIX_FMT_RGB48);

    // Opaque formats are least unlike each other.
    TEST(AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_VDPAU);

    printf("%d tests passed, %d tests failed.\n", pass, fail);
    return !!fail;
}