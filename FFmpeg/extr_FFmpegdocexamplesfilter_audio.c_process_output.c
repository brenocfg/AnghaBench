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
typedef  int uint8_t ;
struct AVMD5 {int dummy; } ;
typedef  int /*<<< orphan*/  checksum ;
struct TYPE_3__ {int nb_samples; int /*<<< orphan*/ * extended_data; int /*<<< orphan*/  format; int /*<<< orphan*/  channel_layout; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 int av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_md5_init (struct AVMD5*) ; 
 int /*<<< orphan*/  av_md5_sum (int*,int /*<<< orphan*/ ,int) ; 
 int av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int process_output(struct AVMD5 *md5, AVFrame *frame)
{
    int planar     = av_sample_fmt_is_planar(frame->format);
    int channels   = av_get_channel_layout_nb_channels(frame->channel_layout);
    int planes     = planar ? channels : 1;
    int bps        = av_get_bytes_per_sample(frame->format);
    int plane_size = bps * frame->nb_samples * (planar ? 1 : channels);
    int i, j;

    for (i = 0; i < planes; i++) {
        uint8_t checksum[16];

        av_md5_init(md5);
        av_md5_sum(checksum, frame->extended_data[i], plane_size);

        fprintf(stdout, "plane %d: 0x", i);
        for (j = 0; j < sizeof(checksum); j++)
            fprintf(stdout, "%02X", checksum[j]);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");

    return 0;
}