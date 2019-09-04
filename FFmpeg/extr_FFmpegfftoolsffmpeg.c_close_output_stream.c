#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  recording_time; scalar_t__ shortest; } ;
struct TYPE_7__ {size_t file_index; TYPE_1__* enc_ctx; scalar_t__ first_pts; scalar_t__ sync_opts; int /*<<< orphan*/  finished; } ;
struct TYPE_6__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ OutputStream ;
typedef  TYPE_3__ OutputFile ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  ENCODER_FINISHED ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__** output_files ; 

__attribute__((used)) static void close_output_stream(OutputStream *ost)
{
    OutputFile *of = output_files[ost->file_index];

    ost->finished |= ENCODER_FINISHED;
    if (of->shortest) {
        int64_t end = av_rescale_q(ost->sync_opts - ost->first_pts, ost->enc_ctx->time_base, AV_TIME_BASE_Q);
        of->recording_time = FFMIN(of->recording_time, end);
    }
}