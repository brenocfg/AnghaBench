#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  put_chroma_pixels_tab; int /*<<< orphan*/  put_pixels_tab; int /*<<< orphan*/  avg_chroma_pixels_tab; int /*<<< orphan*/  avg_pixels_tab; } ;
struct TYPE_7__ {int weight1; TYPE_1__ rdsp; int /*<<< orphan*/  rv30; } ;
typedef  TYPE_2__ RV34DecContext ;

/* Variables and functions */
 int const RV34_MB_B_BIDIR ; 
 int /*<<< orphan*/  rv34_mc (TYPE_2__*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv4_weight (TYPE_2__*) ; 

__attribute__((used)) static void rv34_mc_2mv(RV34DecContext *r, const int block_type)
{
    int weighted = !r->rv30 && block_type != RV34_MB_B_BIDIR && r->weight1 != 8192;

    rv34_mc(r, block_type, 0, 0, 0, 2, 2, 0, r->rv30, weighted,
            r->rdsp.put_pixels_tab,
            r->rdsp.put_chroma_pixels_tab);
    if(!weighted){
        rv34_mc(r, block_type, 0, 0, 0, 2, 2, 1, r->rv30, 0,
                r->rdsp.avg_pixels_tab,
                r->rdsp.avg_chroma_pixels_tab);
    }else{
        rv34_mc(r, block_type, 0, 0, 0, 2, 2, 1, r->rv30, 1,
                r->rdsp.put_pixels_tab,
                r->rdsp.put_chroma_pixels_tab);
        rv4_weight(r);
    }
}