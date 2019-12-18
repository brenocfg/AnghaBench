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
 int /*<<< orphan*/  memmove (double*,double*,int) ; 

__attribute__((used)) static void delete_metric(double * metrics, int pos, int size)
{
    double * dst   = &metrics[pos];
    double * src   = &metrics[pos + 1];
    int msize = (size - (pos + 1)) * sizeof(double);
    memmove(dst, src, msize);
}