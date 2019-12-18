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
typedef  int /*<<< orphan*/  slice_buffer ;
struct TYPE_3__ {int y; void* b3; void* b2; void* b1; void* b0; } ;
typedef  TYPE_1__ DWTCompose ;

/* Variables and functions */
 int avpriv_mirror (int,int) ; 
 void* slice_buffer_get_line (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void spatial_compose97i_buffered_init(DWTCompose *cs, slice_buffer *sb,
                                             int height, int stride_line)
{
    cs->b0 = slice_buffer_get_line(sb, avpriv_mirror(-3 - 1, height - 1) * stride_line);
    cs->b1 = slice_buffer_get_line(sb, avpriv_mirror(-3,     height - 1) * stride_line);
    cs->b2 = slice_buffer_get_line(sb, avpriv_mirror(-3 + 1, height - 1) * stride_line);
    cs->b3 = slice_buffer_get_line(sb, avpriv_mirror(-3 + 2, height - 1) * stride_line);
    cs->y  = -3;
}