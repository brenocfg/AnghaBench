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
struct TYPE_3__ {scalar_t__* v; } ;
typedef  TYPE_1__ AVInteger ;

/* Variables and functions */
 int AV_INTEGER_SIZE ; 
 int av_log2_16bit (scalar_t__) ; 

int av_log2_i(AVInteger a){
    int i;

    for(i=AV_INTEGER_SIZE-1; i>=0; i--){
        if(a.v[i])
            return av_log2_16bit(a.v[i]) + 16*i;
    }
    return -1;
}