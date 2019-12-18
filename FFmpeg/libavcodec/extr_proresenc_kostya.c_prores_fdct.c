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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* fdct ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ FDCTDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prores_fdct(FDCTDSPContext *fdsp, const uint16_t *src,
                        ptrdiff_t linesize, int16_t *block)
{
    int x, y;
    const uint16_t *tsrc = src;

    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++)
            block[y * 8 + x] = tsrc[x];
        tsrc += linesize >> 1;
    }
    fdsp->fdct(block);
}