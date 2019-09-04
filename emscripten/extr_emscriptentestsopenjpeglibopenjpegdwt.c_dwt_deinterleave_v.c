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

__attribute__((used)) static void dwt_deinterleave_v(int *a, int *b, int dn, int sn, int x, int cas) {
    int i;
    for (i=0; i<sn; i++) b[i*x]=a[2*i+cas];
    for (i=0; i<dn; i++) b[(sn+i)*x]=a[(2*i+1-cas)];
}