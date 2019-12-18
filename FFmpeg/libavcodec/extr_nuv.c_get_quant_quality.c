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
struct TYPE_3__ {int* lq; int* cq; } ;
typedef  TYPE_1__ NuvContext ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int* fallback_cquant ; 
 int* fallback_lquant ; 

__attribute__((used)) static void get_quant_quality(NuvContext *c, int quality)
{
    int i;
    quality = FFMAX(quality, 1);
    for (i = 0; i < 64; i++) {
        c->lq[i] = (fallback_lquant[i] << 7) / quality;
        c->cq[i] = (fallback_cquant[i] << 7) / quality;
    }
}