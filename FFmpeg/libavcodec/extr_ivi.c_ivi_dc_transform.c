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
struct TYPE_3__ {int /*<<< orphan*/  pitch; scalar_t__ buf; int /*<<< orphan*/  (* dc_transform ) (int*,scalar_t__,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ IVIBandDesc ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ivi_dc_transform(const IVIBandDesc *band, int *prev_dc, int buf_offs,
                            int blk_size)
{
    band->dc_transform(prev_dc, band->buf + buf_offs,
                       band->pitch, blk_size);

    return 0;
}