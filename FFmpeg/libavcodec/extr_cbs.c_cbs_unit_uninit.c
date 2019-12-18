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
struct TYPE_3__ {scalar_t__ data_bit_padding; scalar_t__ data_size; int /*<<< orphan*/ * data; int /*<<< orphan*/  data_ref; int /*<<< orphan*/ * content; int /*<<< orphan*/  content_ref; } ;
typedef  TYPE_1__ CodedBitstreamUnit ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbs_unit_uninit(CodedBitstreamContext *ctx,
                            CodedBitstreamUnit *unit)
{
    av_buffer_unref(&unit->content_ref);
    unit->content = NULL;

    av_buffer_unref(&unit->data_ref);
    unit->data             = NULL;
    unit->data_size        = 0;
    unit->data_bit_padding = 0;
}