#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* ctx; } ;
struct TYPE_10__ {size_t file_index; TYPE_3__* st; TYPE_1__* decoded_frame; } ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int /*<<< orphan*/  url; } ;
struct TYPE_7__ {int flags; scalar_t__ decode_error_flags; } ;
typedef  TYPE_4__ InputStream ;

/* Variables and functions */
 int AV_FRAME_FLAG_CORRUPT ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * decode_error_stat ; 
 scalar_t__ exit_on_error ; 
 int /*<<< orphan*/  exit_program (int) ; 
 TYPE_5__** input_files ; 

__attribute__((used)) static void check_decode_result(InputStream *ist, int *got_output, int ret)
{
    if (*got_output || ret<0)
        decode_error_stat[ret<0] ++;

    if (ret < 0 && exit_on_error)
        exit_program(1);

    if (*got_output && ist) {
        if (ist->decoded_frame->decode_error_flags || (ist->decoded_frame->flags & AV_FRAME_FLAG_CORRUPT)) {
            av_log(NULL, exit_on_error ? AV_LOG_FATAL : AV_LOG_WARNING,
                   "%s: corrupt decoded frame in stream %d\n", input_files[ist->file_index]->ctx->url, ist->st->index);
            if (exit_on_error)
                exit_program(1);
        }
    }
}