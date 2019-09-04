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
struct TYPE_3__ {int /*<<< orphan*/  buffer; scalar_t__ flags; scalar_t__ data_index; void* dts; void* pts; } ;
typedef  TYPE_1__ PESContext ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_pes_packet_state(PESContext *pes)
{
    pes->pts        = AV_NOPTS_VALUE;
    pes->dts        = AV_NOPTS_VALUE;
    pes->data_index = 0;
    pes->flags      = 0;
    av_buffer_unref(&pes->buffer);
}