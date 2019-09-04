#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* v; } ;
typedef  TYPE_1__ AVInteger ;

/* Variables and functions */
 int AV_INTEGER_SIZE ; 

AVInteger av_shr_i(AVInteger a, int s){
    AVInteger out;
    int i;

    for(i=0; i<AV_INTEGER_SIZE; i++){
        unsigned int index= i + (s>>4);
        unsigned int v=0;
        if(index+1<AV_INTEGER_SIZE) v = a.v[index+1]<<16;
        if(index  <AV_INTEGER_SIZE) v+= a.v[index  ];
        out.v[i]= v >> (s&15);
    }
    return out;
}