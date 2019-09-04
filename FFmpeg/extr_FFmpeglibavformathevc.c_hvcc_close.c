#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_5__ {struct TYPE_5__* nalUnitLength; struct TYPE_5__* nalUnit; scalar_t__ numNalus; } ;
struct TYPE_4__ {size_t numOfArrays; TYPE_3__* array; } ;
typedef  TYPE_1__ HEVCDecoderConfigurationRecord ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 

__attribute__((used)) static void hvcc_close(HEVCDecoderConfigurationRecord *hvcc)
{
    uint8_t i;

    for (i = 0; i < hvcc->numOfArrays; i++) {
        hvcc->array[i].numNalus = 0;
        av_freep(&hvcc->array[i].nalUnit);
        av_freep(&hvcc->array[i].nalUnitLength);
    }

    hvcc->numOfArrays = 0;
    av_freep(&hvcc->array);
}