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
struct TYPE_3__ {int* filters; int* prevfilt; int* cvector; int /*<<< orphan*/  flag; } ;
typedef  TYPE_1__ TSContext ;

/* Variables and functions */

__attribute__((used)) static void truespeech_filters_merge(TSContext *dec)
{
    int i;

    if(!dec->flag){
        for(i = 0; i < 8; i++){
            dec->filters[i + 0] = dec->prevfilt[i];
            dec->filters[i + 8] = dec->prevfilt[i];
        }
    }else{
        for(i = 0; i < 8; i++){
            dec->filters[i + 0]=(dec->cvector[i] * 21846 + dec->prevfilt[i] * 10923 + 16384) >> 15;
            dec->filters[i + 8]=(dec->cvector[i] * 10923 + dec->prevfilt[i] * 21846 + 16384) >> 15;
        }
    }
    for(i = 0; i < 8; i++){
        dec->filters[i + 16] = dec->cvector[i];
        dec->filters[i + 24] = dec->cvector[i];
    }
}