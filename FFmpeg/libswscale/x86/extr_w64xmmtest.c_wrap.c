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
typedef  int /*<<< orphan*/  wrap ;
typedef  int /*<<< orphan*/  uint8_t ;
struct SwsContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  testxmmclobbers (int /*<<< orphan*/  (*) (struct SwsContext*,int /*<<< orphan*/  const* const*,int const*,int,int,int /*<<< orphan*/ * const*,int const*),struct SwsContext*,int /*<<< orphan*/  const* const*,int const*,int,int,int /*<<< orphan*/ * const*,int const*) ; 

wrap(sws_scale(struct SwsContext *c, const uint8_t *const srcSlice[],
               const int srcStride[], int srcSliceY, int srcSliceH,
               uint8_t *const dst[], const int dstStride[]))
{
    testxmmclobbers(sws_scale, c, srcSlice, srcStride, srcSliceY,
                    srcSliceH, dst, dstStride);
}