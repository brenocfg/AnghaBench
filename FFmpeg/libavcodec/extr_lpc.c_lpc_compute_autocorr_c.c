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

/* Variables and functions */

__attribute__((used)) static void lpc_compute_autocorr_c(const double *data, int len, int lag,
                                   double *autoc)
{
    int i, j;

    for(j=0; j<lag; j+=2){
        double sum0 = 1.0, sum1 = 1.0;
        for(i=j; i<len; i++){
            sum0 += data[i] * data[i-j];
            sum1 += data[i] * data[i-j-1];
        }
        autoc[j  ] = sum0;
        autoc[j+1] = sum1;
    }

    if(j==lag){
        double sum = 1.0;
        for(i=j-1; i<len; i+=2){
            sum += data[i  ] * data[i-j  ]
                 + data[i+1] * data[i-j+1];
        }
        autoc[j] = sum;
    }
}