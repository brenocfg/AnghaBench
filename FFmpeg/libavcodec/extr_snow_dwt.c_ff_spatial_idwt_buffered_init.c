#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  slice_buffer ;
typedef  int /*<<< orphan*/  DWTCompose ;

/* Variables and functions */
#define  DWT_53 129 
#define  DWT_97 128 
 int /*<<< orphan*/  spatial_compose53i_buffered_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spatial_compose97i_buffered_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void ff_spatial_idwt_buffered_init(DWTCompose *cs, slice_buffer *sb, int width,
                                   int height, int stride_line, int type,
                                   int decomposition_count)
{
    int level;
    for (level = decomposition_count - 1; level >= 0; level--) {
        switch (type) {
        case DWT_97:
            spatial_compose97i_buffered_init(cs + level, sb, height >> level,
                                             stride_line << level);
            break;
        case DWT_53:
            spatial_compose53i_buffered_init(cs + level, sb, height >> level,
                                             stride_line << level);
            break;
        }
    }
}