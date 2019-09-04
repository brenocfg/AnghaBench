#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nb_frames; int /*<<< orphan*/  time_base; } ;
struct TYPE_6__ {scalar_t__ codec_type; int flags; double width; double height; int /*<<< orphan*/  time_base; } ;
struct TYPE_5__ {float quality; int file_index; int index; double* error; int data_size; int /*<<< orphan*/  pict_type; TYPE_4__* st; TYPE_2__* enc_ctx; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int AV_CODEC_FLAG_PSNR ; 
 scalar_t__ FF_QP2LAMBDA ; 
 int av_get_picture_type_char (int /*<<< orphan*/ ) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int av_stream_get_end_pts (TYPE_4__*) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 double psnr (double) ; 
 scalar_t__ vstats_file ; 
 int /*<<< orphan*/  vstats_filename ; 
 int vstats_version ; 

__attribute__((used)) static void do_video_stats(OutputStream *ost, int frame_size)
{
    AVCodecContext *enc;
    int frame_number;
    double ti1, bitrate, avg_bitrate;

    /* this is executed just the first time do_video_stats is called */
    if (!vstats_file) {
        vstats_file = fopen(vstats_filename, "w");
        if (!vstats_file) {
            perror("fopen");
            exit_program(1);
        }
    }

    enc = ost->enc_ctx;
    if (enc->codec_type == AVMEDIA_TYPE_VIDEO) {
        frame_number = ost->st->nb_frames;
        if (vstats_version <= 1) {
            fprintf(vstats_file, "frame= %5d q= %2.1f ", frame_number,
                    ost->quality / (float)FF_QP2LAMBDA);
        } else  {
            fprintf(vstats_file, "out= %2d st= %2d frame= %5d q= %2.1f ", ost->file_index, ost->index, frame_number,
                    ost->quality / (float)FF_QP2LAMBDA);
        }

        if (ost->error[0]>=0 && (enc->flags & AV_CODEC_FLAG_PSNR))
            fprintf(vstats_file, "PSNR= %6.2f ", psnr(ost->error[0] / (enc->width * enc->height * 255.0 * 255.0)));

        fprintf(vstats_file,"f_size= %6d ", frame_size);
        /* compute pts value */
        ti1 = av_stream_get_end_pts(ost->st) * av_q2d(ost->st->time_base);
        if (ti1 < 0.01)
            ti1 = 0.01;

        bitrate     = (frame_size * 8) / av_q2d(enc->time_base) / 1000.0;
        avg_bitrate = (double)(ost->data_size * 8) / ti1 / 1000.0;
        fprintf(vstats_file, "s_size= %8.0fkB time= %0.3f br= %7.1fkbits/s avg_br= %7.1fkbits/s ",
               (double)ost->data_size / 1024, ti1, bitrate, avg_bitrate);
        fprintf(vstats_file, "type= %c\n", av_get_picture_type_char(ost->pict_type));
    }
}