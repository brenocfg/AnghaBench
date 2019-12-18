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
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static void encode_residual_fixed(int32_t *res, const int32_t *smp, int n,
                                  int order)
{
    int i;

    for (i = 0; i < order; i++)
        res[i] = smp[i];

    if (order == 0) {
        for (i = order; i < n; i++)
            res[i] = smp[i];
    } else if (order == 1) {
        for (i = order; i < n; i++)
            res[i] = smp[i] - smp[i-1];
    } else if (order == 2) {
        int a = smp[order-1] - smp[order-2];
        for (i = order; i < n; i += 2) {
            int b    = smp[i  ] - smp[i-1];
            res[i]   = b - a;
            a        = smp[i+1] - smp[i  ];
            res[i+1] = a - b;
        }
    } else if (order == 3) {
        int a = smp[order-1] -   smp[order-2];
        int c = smp[order-1] - 2*smp[order-2] + smp[order-3];
        for (i = order; i < n; i += 2) {
            int b    = smp[i  ] - smp[i-1];
            int d    = b - a;
            res[i]   = d - c;
            a        = smp[i+1] - smp[i  ];
            c        = a - b;
            res[i+1] = c - d;
        }
    } else {
        int a = smp[order-1] -   smp[order-2];
        int c = smp[order-1] - 2*smp[order-2] +   smp[order-3];
        int e = smp[order-1] - 3*smp[order-2] + 3*smp[order-3] - smp[order-4];
        for (i = order; i < n; i += 2) {
            int b    = smp[i  ] - smp[i-1];
            int d    = b - a;
            int f    = d - c;
            res[i  ] = f - e;
            a        = smp[i+1] - smp[i  ];
            c        = a - b;
            e        = c - d;
            res[i+1] = e - f;
        }
    }
}