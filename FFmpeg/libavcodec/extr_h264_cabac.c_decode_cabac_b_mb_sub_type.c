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

__attribute__((used)) static int decode_cabac_b_mb_sub_type(H264SliceContext *sl)
{
    int type;
    if( !get_cabac( &sl->cabac, &sl->cabac_state[36] ) )
        return 0;   /* B_Direct_8x8 */
    if( !get_cabac( &sl->cabac, &sl->cabac_state[37] ) )
        return 1 + get_cabac( &sl->cabac, &sl->cabac_state[39] ); /* B_L0_8x8, B_L1_8x8 */
    type = 3;
    if( get_cabac( &sl->cabac, &sl->cabac_state[38] ) ) {
        if( get_cabac( &sl->cabac, &sl->cabac_state[39] ) )
            return 11 + get_cabac( &sl->cabac, &sl->cabac_state[39] ); /* B_L1_4x4, B_Bi_4x4 */
        type += 4;
    }
    type += 2*get_cabac( &sl->cabac, &sl->cabac_state[39] );
    type +=   get_cabac( &sl->cabac, &sl->cabac_state[39] );
    return type;
}