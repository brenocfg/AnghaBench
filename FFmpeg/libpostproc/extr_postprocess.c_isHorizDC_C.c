#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int baseDcDiff; int flatnessThreshold; } ;
struct TYPE_5__ {int nonBQP; TYPE_1__ ppMode; } ;
typedef  TYPE_2__ PPContext ;

/* Variables and functions */
 int BLOCK_SIZE ; 

__attribute__((used)) static inline int isHorizDC_C(const uint8_t src[], int stride, const PPContext *c)
{
    int numEq= 0;
    int y;
    const int dcOffset= ((c->nonBQP*c->ppMode.baseDcDiff)>>8) + 1;
    const int dcThreshold= dcOffset*2 + 1;

    for(y=0; y<BLOCK_SIZE; y++){
        numEq += ((unsigned)(src[0] - src[1] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[1] - src[2] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[2] - src[3] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[3] - src[4] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[4] - src[5] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[5] - src[6] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[6] - src[7] + dcOffset)) < dcThreshold;
        src+= stride;
    }
    return numEq > c->ppMode.flatnessThreshold;
}