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
struct TYPE_3__ {int /*<<< orphan*/ * cabac_state; int /*<<< orphan*/  cabac; } ;
typedef  TYPE_1__ H264SliceContext ;

/* Variables and functions */
 int get_cabac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_cabac_mb_intra4x4_pred_mode(H264SliceContext *sl, int pred_mode)
{
    int mode = 0;

    if( get_cabac( &sl->cabac, &sl->cabac_state[68] ) )
        return pred_mode;

    mode += 1 * get_cabac( &sl->cabac, &sl->cabac_state[69] );
    mode += 2 * get_cabac( &sl->cabac, &sl->cabac_state[69] );
    mode += 4 * get_cabac( &sl->cabac, &sl->cabac_state[69] );

    return mode + ( mode >= pred_mode );
}