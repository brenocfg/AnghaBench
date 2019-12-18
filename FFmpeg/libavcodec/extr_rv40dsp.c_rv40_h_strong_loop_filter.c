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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  rv40_strong_loop_filter (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int,int const,int const,int const,int const) ; 

__attribute__((used)) static void rv40_h_strong_loop_filter(uint8_t *src, const ptrdiff_t stride,
                                      const int alpha, const int lims,
                                      const int dmode, const int chroma)
{
    rv40_strong_loop_filter(src, stride, 1, alpha, lims, dmode, chroma);
}