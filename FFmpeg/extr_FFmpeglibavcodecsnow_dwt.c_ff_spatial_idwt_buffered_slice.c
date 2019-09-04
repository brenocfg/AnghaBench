#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  slice_buffer ;
struct TYPE_5__ {scalar_t__ y; } ;
typedef  int /*<<< orphan*/  SnowDWTContext ;
typedef  int /*<<< orphan*/  IDWTELEM ;
typedef  TYPE_1__ DWTCompose ;

/* Variables and functions */
#define  DWT_53 129 
#define  DWT_97 128 
 scalar_t__ FFMIN (int,int) ; 
 int /*<<< orphan*/  spatial_compose53i_dy_buffered (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  spatial_compose97i_dy_buffered (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

void ff_spatial_idwt_buffered_slice(SnowDWTContext *dsp, DWTCompose *cs,
                                    slice_buffer *slice_buf, IDWTELEM *temp,
                                    int width, int height, int stride_line,
                                    int type, int decomposition_count, int y)
{
    const int support = type == 1 ? 3 : 5;
    int level;
    if (type == 2)
        return;

    for (level = decomposition_count - 1; level >= 0; level--)
        while (cs[level].y <= FFMIN((y >> level) + support, height >> level)) {
            switch (type) {
            case DWT_97:
                spatial_compose97i_dy_buffered(dsp, cs + level, slice_buf, temp,
                                               width >> level,
                                               height >> level,
                                               stride_line << level);
                break;
            case DWT_53:
                spatial_compose53i_dy_buffered(cs + level, slice_buf, temp,
                                               width >> level,
                                               height >> level,
                                               stride_line << level);
                break;
            }
        }
}