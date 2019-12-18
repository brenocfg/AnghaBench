#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 float CrossCorrelation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t SBC_LHIST ; 
 size_t SBC_M ; 
 int SBC_N ; 

__attribute__((used)) static int PatternMatch(int16_t *y){
    int   n;
    float maxCn = -999999.0;  // large negative number
    float Cn;
    int   bestmatch = 0;

    for (n = 0; n < SBC_N; n++){
        Cn = CrossCorrelation(&y[SBC_LHIST-SBC_M], &y[n]);
        if (Cn > maxCn){
            bestmatch = n;
            maxCn = Cn;
        }
    }
    return bestmatch;
}