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
struct TYPE_3__ {int** thres2; } ;
typedef  TYPE_1__ PP7Context ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int SN0 ; 
 int SN2 ; 

__attribute__((used)) static void init_thres2(PP7Context *p)
{
    int qp, i;
    int bias = 0; //FIXME

    for (qp = 0; qp < 99; qp++) {
        for (i = 0; i < 16; i++) {
            p->thres2[qp][i] = ((i&1) ? SN2 : SN0) * ((i&4) ? SN2 : SN0) * FFMAX(1, qp) * (1<<2) - 1 - bias;
        }
    }
}