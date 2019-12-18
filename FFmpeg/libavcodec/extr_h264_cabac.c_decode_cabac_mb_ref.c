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
struct TYPE_3__ {int** ref_cache; scalar_t__ slice_type_nos; int* direct_cache; int /*<<< orphan*/ * cabac_state; int /*<<< orphan*/  cabac; } ;
typedef  TYPE_1__ H264SliceContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int MB_TYPE_DIRECT2 ; 
 scalar_t__ get_cabac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* scan8 ; 

__attribute__((used)) static int decode_cabac_mb_ref(H264SliceContext *sl, int list, int n)
{
    int refa = sl->ref_cache[list][scan8[n] - 1];
    int refb = sl->ref_cache[list][scan8[n] - 8];
    int ref  = 0;
    int ctx  = 0;

    if (sl->slice_type_nos == AV_PICTURE_TYPE_B) {
        if( refa > 0 && !(sl->direct_cache[scan8[n] - 1]&(MB_TYPE_DIRECT2>>1)) )
            ctx++;
        if( refb > 0 && !(sl->direct_cache[scan8[n] - 8]&(MB_TYPE_DIRECT2>>1)) )
            ctx += 2;
    } else {
        if( refa > 0 )
            ctx++;
        if( refb > 0 )
            ctx += 2;
    }

    while( get_cabac( &sl->cabac, &sl->cabac_state[54+ctx] ) ) {
        ref++;
        ctx = (ctx>>2)+4;
        if(ref >= 32 /*h->ref_list[list]*/){
            return -1;
        }
    }
    return ref;
}