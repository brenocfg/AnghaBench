#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* p; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_LENGTH_DWORDS_P192 ; 
 TYPE_1__ curve ; 
 scalar_t__ multiprecision_compare (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_sub (int*,int*,int*,int /*<<< orphan*/ ) ; 

void multiprecision_fast_mod(DWORD *c, DWORD *a)
{
    DWORD U;
    DWORD V;
    DWORD *modp = curve.p;

    c[0] = a[0] + a[6];
    U = c[0] < a[0];
    c[0] += a[10];
    U += c[0] < a[10];

    c[1] = a[1] + U;
    U = c[1] < a[1];
    c[1] += a[7];
    U += c[1] < a[7];
    c[1] += a[11];
    U += c[1] < a[11];

    c[2] = a[2] + U;
    U = c[2] < a[2];
    c[2] += a[6];
    U += c[2] < a[6];
    c[2] += a[8];
    U += c[2] < a[8];
    c[2] += a[10];
    U += c[2] < a[10];

    c[3] = a[3] + U;
    U = c[3] < a[3];
    c[3] += a[7];
    U += c[3] < a[7];
    c[3] += a[9];
    U += c[3] < a[9];
    c[3] += a[11];
    U += c[3] < a[11];

    c[4] = a[4] + U;
    U = c[4] < a[4];
    c[4] += a[8];
    U += c[4] < a[8];
    c[4] += a[10];
    U += c[4] < a[10];

    c[5] = a[5] + U;
    U = c[5] < a[5];
    c[5] += a[9];
    U += c[5] < a[9];
    c[5] += a[11];
    U += c[5] < a[11];

    c[0] += U;
    V = c[0] < U;
    c[1] += V;
    V = c[1] < V;
    c[2] += V;
    V = c[2] < V;
    c[2] += U;
    V = c[2] < U;
    c[3] += V;
    V = c[3] < V;
    c[4] += V;
    V = c[4] < V;
    c[5] += V;
    V = c[5] < V;

    if (V) {
        multiprecision_sub(c, c, modp, KEY_LENGTH_DWORDS_P192);
    } else if (multiprecision_compare(c, modp, KEY_LENGTH_DWORDS_P192) >= 0) {
        multiprecision_sub(c, c, modp, KEY_LENGTH_DWORDS_P192);
    }
}