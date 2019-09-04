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
 int gsm_mult (int,int) ; 

__attribute__((used)) static int filter_value(int in, int rrp[8], int v[9])
{
    int i;
    for (i = 7; i >= 0; i--) {
        in -= gsm_mult(rrp[i], v[i]);
        v[i + 1] = v[i] + gsm_mult(rrp[i], in);
    }
    v[0] = in;
    return in;
}