#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int text_pos; int byte_count; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ MovTextContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_append_data (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void mov_text_new_line_cb(void *priv, int forced)
{
    MovTextContext *s = priv;
    av_bprint_append_data(&s->buffer, "\n", 1);
    s->text_pos += 1;
    s->byte_count += 1;
}