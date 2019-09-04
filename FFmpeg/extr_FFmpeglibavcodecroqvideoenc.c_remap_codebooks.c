#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* cb4x4; scalar_t__ quake3_compat; } ;
struct TYPE_8__ {scalar_t__* usedCB2; scalar_t__* usedCB4; } ;
struct TYPE_9__ {int* i2f4; int* f2i4; int numCB4; int* i2f2; int* f2i2; int numCB2; TYPE_2__ codebooks; } ;
struct TYPE_7__ {size_t* idx; } ;
typedef  TYPE_3__ RoqTempdata ;
typedef  TYPE_4__ RoqContext ;

/* Variables and functions */
 int MAX_CBS_2x2 ; 
 int MAX_CBS_4x4 ; 

__attribute__((used)) static void remap_codebooks(RoqContext *enc, RoqTempdata *tempData)
{
    int i, j, idx=0;

    /* Make remaps for the final codebook usage */
    for (i=0; i<(enc->quake3_compat ? MAX_CBS_4x4-1 : MAX_CBS_4x4); i++) {
        if (tempData->codebooks.usedCB4[i]) {
            tempData->i2f4[i] = idx;
            tempData->f2i4[idx] = i;
            for (j=0; j<4; j++)
                tempData->codebooks.usedCB2[enc->cb4x4[i].idx[j]]++;
            idx++;
        }
    }

    tempData->numCB4 = idx;

    idx = 0;
    for (i=0; i<MAX_CBS_2x2; i++) {
        if (tempData->codebooks.usedCB2[i]) {
            tempData->i2f2[i] = idx;
            tempData->f2i2[idx] = i;
            idx++;
        }
    }
    tempData->numCB2 = idx;

}