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
 scalar_t__ get_cabac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_cabac_p_mb_sub_type(H264SliceContext *sl)
{
    if( get_cabac( &sl->cabac, &sl->cabac_state[21] ) )
        return 0;   /* 8x8 */
    if( !get_cabac( &sl->cabac, &sl->cabac_state[22] ) )
        return 1;   /* 8x4 */
    if( get_cabac( &sl->cabac, &sl->cabac_state[23] ) )
        return 2;   /* 4x8 */
    return 3;       /* 4x4 */
}