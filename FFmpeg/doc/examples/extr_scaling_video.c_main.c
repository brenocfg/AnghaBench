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
struct SwsContext {int dummy; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PIX_FMT_RGB24 ; 
 int AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SWS_BILINEAR ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 char* av_get_pix_fmt_name (int) ; 
 int av_image_alloc (int /*<<< orphan*/ **,int*,int,int,int,int) ; 
 scalar_t__ av_parse_video_size (int*,int*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_yuv_image (int /*<<< orphan*/ **,int*,int,int,int) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sws_freeContext (struct SwsContext*) ; 
 struct SwsContext* sws_getContext (int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_scale (struct SwsContext*,int /*<<< orphan*/  const* const*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int*) ; 

int main(int argc, char **argv)
{
    uint8_t *src_data[4], *dst_data[4];
    int src_linesize[4], dst_linesize[4];
    int src_w = 320, src_h = 240, dst_w, dst_h;
    enum AVPixelFormat src_pix_fmt = AV_PIX_FMT_YUV420P, dst_pix_fmt = AV_PIX_FMT_RGB24;
    const char *dst_size = NULL;
    const char *dst_filename = NULL;
    FILE *dst_file;
    int dst_bufsize;
    struct SwsContext *sws_ctx;
    int i, ret;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s output_file output_size\n"
                "API example program to show how to scale an image with libswscale.\n"
                "This program generates a series of pictures, rescales them to the given "
                "output_size and saves them to an output file named output_file\n."
                "\n", argv[0]);
        exit(1);
    }
    dst_filename = argv[1];
    dst_size     = argv[2];

    if (av_parse_video_size(&dst_w, &dst_h, dst_size) < 0) {
        fprintf(stderr,
                "Invalid size '%s', must be in the form WxH or a valid size abbreviation\n",
                dst_size);
        exit(1);
    }

    dst_file = fopen(dst_filename, "wb");
    if (!dst_file) {
        fprintf(stderr, "Could not open destination file %s\n", dst_filename);
        exit(1);
    }

    /* create scaling context */
    sws_ctx = sws_getContext(src_w, src_h, src_pix_fmt,
                             dst_w, dst_h, dst_pix_fmt,
                             SWS_BILINEAR, NULL, NULL, NULL);
    if (!sws_ctx) {
        fprintf(stderr,
                "Impossible to create scale context for the conversion "
                "fmt:%s s:%dx%d -> fmt:%s s:%dx%d\n",
                av_get_pix_fmt_name(src_pix_fmt), src_w, src_h,
                av_get_pix_fmt_name(dst_pix_fmt), dst_w, dst_h);
        ret = AVERROR(EINVAL);
        goto end;
    }

    /* allocate source and destination image buffers */
    if ((ret = av_image_alloc(src_data, src_linesize,
                              src_w, src_h, src_pix_fmt, 16)) < 0) {
        fprintf(stderr, "Could not allocate source image\n");
        goto end;
    }

    /* buffer is going to be written to rawvideo file, no alignment */
    if ((ret = av_image_alloc(dst_data, dst_linesize,
                              dst_w, dst_h, dst_pix_fmt, 1)) < 0) {
        fprintf(stderr, "Could not allocate destination image\n");
        goto end;
    }
    dst_bufsize = ret;

    for (i = 0; i < 100; i++) {
        /* generate synthetic video */
        fill_yuv_image(src_data, src_linesize, src_w, src_h, i);

        /* convert to destination format */
        sws_scale(sws_ctx, (const uint8_t * const*)src_data,
                  src_linesize, 0, src_h, dst_data, dst_linesize);

        /* write scaled image to file */
        fwrite(dst_data[0], 1, dst_bufsize, dst_file);
    }

    fprintf(stderr, "Scaling succeeded. Play the output file with the command:\n"
           "ffplay -f rawvideo -pix_fmt %s -video_size %dx%d %s\n",
           av_get_pix_fmt_name(dst_pix_fmt), dst_w, dst_h, dst_filename);

end:
    fclose(dst_file);
    av_freep(&src_data[0]);
    av_freep(&dst_data[0]);
    sws_freeContext(sws_ctx);
    return ret < 0;
}