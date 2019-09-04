#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_blocks; int /*<<< orphan*/  (* output_frame_header ) (TYPE_1__*) ;int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AC3EncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  AC3_MAX_CODED_FRAME_SIZE ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_audio_block (TYPE_1__*,int) ; 
 int /*<<< orphan*/  output_frame_end (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void ff_ac3_output_frame(AC3EncodeContext *s, unsigned char *frame)
{
    int blk;

    init_put_bits(&s->pb, frame, AC3_MAX_CODED_FRAME_SIZE);

    s->output_frame_header(s);

    for (blk = 0; blk < s->num_blocks; blk++)
        output_audio_block(s, blk);

    output_frame_end(s);
}