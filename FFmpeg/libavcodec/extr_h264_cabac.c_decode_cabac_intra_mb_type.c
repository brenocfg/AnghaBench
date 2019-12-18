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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int* left_type; int top_type; int /*<<< orphan*/  cabac; int /*<<< orphan*/ * cabac_state; } ;
typedef  TYPE_1__ H264SliceContext ;

/* Variables and functions */
 size_t LTOP ; 
 int MB_TYPE_INTRA16x16 ; 
 int MB_TYPE_INTRA_PCM ; 
 int get_cabac_noinline (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_cabac_terminate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_cabac_intra_mb_type(H264SliceContext *sl,
                                      int ctx_base, int intra_slice)
{
    uint8_t *state= &sl->cabac_state[ctx_base];
    int mb_type;

    if(intra_slice){
        int ctx=0;
        if (sl->left_type[LTOP] & (MB_TYPE_INTRA16x16|MB_TYPE_INTRA_PCM))
            ctx++;
        if (sl->top_type        & (MB_TYPE_INTRA16x16|MB_TYPE_INTRA_PCM))
            ctx++;
        if( get_cabac_noinline( &sl->cabac, &state[ctx] ) == 0 )
            return 0;   /* I4x4 */
        state += 2;
    }else{
        if( get_cabac_noinline( &sl->cabac, state ) == 0 )
            return 0;   /* I4x4 */
    }

    if( get_cabac_terminate( &sl->cabac ) )
        return 25;  /* PCM */

    mb_type = 1; /* I16x16 */
    mb_type += 12 * get_cabac_noinline( &sl->cabac, &state[1] ); /* cbp_luma != 0 */
    if( get_cabac_noinline( &sl->cabac, &state[2] ) ) /* cbp_chroma */
        mb_type += 4 + 4 * get_cabac_noinline( &sl->cabac, &state[2+intra_slice] );
    mb_type += 2 * get_cabac_noinline( &sl->cabac, &state[3+intra_slice] );
    mb_type += 1 * get_cabac_noinline( &sl->cabac, &state[3+2*intra_slice] );
    return mb_type;
}