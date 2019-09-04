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
typedef  int /*<<< orphan*/  IDWTELEM ;
typedef  int /*<<< orphan*/  DWTCompose ;

/* Variables and functions */
 int MAX_DECOMPOSITIONS ; 
 int /*<<< orphan*/  spatial_idwt_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  spatial_idwt_slice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 

void ff_spatial_idwt(IDWTELEM *buffer, IDWTELEM *temp, int width, int height,
                     int stride, int type, int decomposition_count)
{
    DWTCompose cs[MAX_DECOMPOSITIONS];
    int y;
    spatial_idwt_init(cs, buffer, width, height, stride, type,
                         decomposition_count);
    for (y = 0; y < height; y += 4)
        spatial_idwt_slice(cs, buffer, temp, width, height, stride, type,
                              decomposition_count, y);
}