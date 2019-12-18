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
struct TYPE_6__ {scalar_t__* chroma_pred_mode_table; } ;
struct TYPE_5__ {int* left_mb_xy; int top_mb_xy; int /*<<< orphan*/ * cabac_state; int /*<<< orphan*/  cabac; scalar_t__ top_type; scalar_t__* left_type; } ;
typedef  TYPE_1__ H264SliceContext ;
typedef  TYPE_2__ H264Context ;

/* Variables and functions */
 size_t LTOP ; 
 scalar_t__ get_cabac_noinline (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_cabac_mb_chroma_pre_mode(const H264Context *h, H264SliceContext *sl)
{
    const int mba_xy = sl->left_mb_xy[0];
    const int mbb_xy = sl->top_mb_xy;

    int ctx = 0;

    /* No need to test for IS_INTRA4x4 and IS_INTRA16x16, as we set chroma_pred_mode_table to 0 */
    if (sl->left_type[LTOP] && h->chroma_pred_mode_table[mba_xy] != 0)
        ctx++;

    if (sl->top_type        && h->chroma_pred_mode_table[mbb_xy] != 0)
        ctx++;

    if( get_cabac_noinline( &sl->cabac, &sl->cabac_state[64+ctx] ) == 0 )
        return 0;

    if( get_cabac_noinline( &sl->cabac, &sl->cabac_state[64+3] ) == 0 )
        return 1;
    if( get_cabac_noinline( &sl->cabac, &sl->cabac_state[64+3] ) == 0 )
        return 2;
    else
        return 3;
}