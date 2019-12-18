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
struct TYPE_3__ {int y; int* b0; int* b1; } ;
typedef  int IDWTELEM ;
typedef  TYPE_1__ DWTCompose ;

/* Variables and functions */
 int avpriv_mirror (int,int) ; 
 int /*<<< orphan*/  horizontal_compose53i (int*,int*,int) ; 
 int* slice_buffer_get_line (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vertical_compose53iH0 (int*,int*,int*,int) ; 
 int /*<<< orphan*/  vertical_compose53iL0 (int*,int*,int*,int) ; 

__attribute__((used)) static void spatial_compose53i_dy_buffered(DWTCompose *cs, slice_buffer *sb,
                                           IDWTELEM *temp,
                                           int width, int height,
                                           int stride_line)
{
    int y = cs->y;

    IDWTELEM *b0 = cs->b0;
    IDWTELEM *b1 = cs->b1;
    IDWTELEM *b2 = slice_buffer_get_line(sb,
                                         avpriv_mirror(y + 1, height - 1) *
                                         stride_line);
    IDWTELEM *b3 = slice_buffer_get_line(sb,
                                         avpriv_mirror(y + 2, height - 1) *
                                         stride_line);

    if (y + 1 < (unsigned)height && y < (unsigned)height) {
        int x;

        for (x = 0; x < width; x++) {
            b2[x] -= (b1[x] + b3[x] + 2) >> 2;
            b1[x] += (b0[x] + b2[x])     >> 1;
        }
    } else {
        if (y + 1 < (unsigned)height)
            vertical_compose53iL0(b1, b2, b3, width);
        if (y + 0 < (unsigned)height)
            vertical_compose53iH0(b0, b1, b2, width);
    }

    if (y - 1 < (unsigned)height)
        horizontal_compose53i(b0, temp, width);
    if (y + 0 < (unsigned)height)
        horizontal_compose53i(b1, temp, width);

    cs->b0  = b2;
    cs->b1  = b3;
    cs->y  += 2;
}