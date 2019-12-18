#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  put_chroma_pixels_tab; int /*<<< orphan*/  put_pixels_tab; } ;
struct TYPE_6__ {TYPE_1__ rdsp; int /*<<< orphan*/  rv30; } ;
typedef  TYPE_2__ RV34DecContext ;

/* Variables and functions */
 int /*<<< orphan*/  rv34_mc (TYPE_2__*,int const,int const,int const,int,int const,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv34_mc_1mv(RV34DecContext *r, const int block_type,
                        const int xoff, const int yoff, int mv_off,
                        const int width, const int height, int dir)
{
    rv34_mc(r, block_type, xoff, yoff, mv_off, width, height, dir, r->rv30, 0,
            r->rdsp.put_pixels_tab,
            r->rdsp.put_chroma_pixels_tab);
}