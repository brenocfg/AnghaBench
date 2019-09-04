#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; scalar_t__ pb; } ;
struct TYPE_8__ {scalar_t__ limit_filesize; int ost_index; TYPE_3__* ctx; } ;
struct TYPE_7__ {size_t file_index; scalar_t__ frame_number; scalar_t__ max_frames; scalar_t__ finished; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ OutputFile ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ avio_tell (scalar_t__) ; 
 int /*<<< orphan*/  close_output_stream (TYPE_1__*) ; 
 int nb_output_streams ; 
 TYPE_2__** output_files ; 
 TYPE_1__** output_streams ; 

__attribute__((used)) static int need_output(void)
{
    int i;

    for (i = 0; i < nb_output_streams; i++) {
        OutputStream *ost    = output_streams[i];
        OutputFile *of       = output_files[ost->file_index];
        AVFormatContext *os  = output_files[ost->file_index]->ctx;

        if (ost->finished ||
            (os->pb && avio_tell(os->pb) >= of->limit_filesize))
            continue;
        if (ost->frame_number >= ost->max_frames) {
            int j;
            for (j = 0; j < of->ctx->nb_streams; j++)
                close_output_stream(output_streams[of->ost_index + j]);
            continue;
        }

        return 1;
    }

    return 0;
}