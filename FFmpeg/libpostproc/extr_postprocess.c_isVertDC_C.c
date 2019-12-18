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

__attribute__((used)) static inline int isVertDC_C(const uint8_t src[], int stride, const PPContext *c)
{
    int numEq= 0;
    int y;
    const int dcOffset= ((c->nonBQP*c->ppMode.baseDcDiff)>>8) + 1;
    const int dcThreshold= dcOffset*2 + 1;

    src+= stride*4; // src points to begin of the 8x8 Block
    for(y=0; y<BLOCK_SIZE-1; y++){
        numEq += ((unsigned)(src[0] - src[0+stride] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[1] - src[1+stride] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[2] - src[2+stride] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[3] - src[3+stride] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[4] - src[4+stride] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[5] - src[5+stride] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[6] - src[6+stride] + dcOffset)) < dcThreshold;
        numEq += ((unsigned)(src[7] - src[7+stride] + dcOffset)) < dcThreshold;
        src+= stride;
    }
    return numEq > c->ppMode.flatnessThreshold;
}