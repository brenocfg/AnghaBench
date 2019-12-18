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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  dwtcoef ;
typedef  int /*<<< orphan*/  VC2TransformContext ;

/* Variables and functions */
 int /*<<< orphan*/  dwt_haar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc2_subband_dwt_haar(VC2TransformContext *t, dwtcoef *data,
                                 ptrdiff_t stride, int width, int height)
{
    dwt_haar(t, data, stride, width, height, 0);
}