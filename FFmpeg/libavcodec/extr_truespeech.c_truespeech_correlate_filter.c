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
typedef  int int16_t ;
struct TYPE_3__ {int* cvector; int* vector; int filtval; } ;
typedef  TYPE_1__ TSContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* ts_decay_994_1000 ; 

__attribute__((used)) static void truespeech_correlate_filter(TSContext *dec)
{
    int16_t tmp[8];
    int i, j;

    for(i = 0; i < 8; i++){
        if(i > 0){
            memcpy(tmp, dec->cvector, i * sizeof(*tmp));
            for(j = 0; j < i; j++)
                dec->cvector[j] += (tmp[i - j - 1] * dec->vector[i] + 0x4000) >> 15;
        }
        dec->cvector[i] = (8 - dec->vector[i]) >> 3;
    }
    for(i = 0; i < 8; i++)
        dec->cvector[i] = (dec->cvector[i] * ts_decay_994_1000[i]) >> 15;

    dec->filtval = dec->vector[0];
}