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

__attribute__((used)) static void celt_fir5(const float *x,
                      const float *num,
                      float *y,
                      int N,
                      float *mem)
{
    float num0, num1, num2, num3, num4;
    float mem0, mem1, mem2, mem3, mem4;

    num0 = num[0];
    num1 = num[1];
    num2 = num[2];
    num3 = num[3];
    num4 = num[4];
    mem0 = mem[0];
    mem1 = mem[1];
    mem2 = mem[2];
    mem3 = mem[3];
    mem4 = mem[4];

    for (int i = 0; i < N; i++) {
        float sum = x[i];

        sum += (num0*mem0);
        sum += (num1*mem1);
        sum += (num2*mem2);
        sum += (num3*mem3);
        sum += (num4*mem4);
        mem4 = mem3;
        mem3 = mem2;
        mem2 = mem1;
        mem1 = mem0;
        mem0 = x[i];
        y[i] = sum;
    }

    mem[0] = mem0;
    mem[1] = mem1;
    mem[2] = mem2;
    mem[3] = mem3;
    mem[4] = mem4;
}