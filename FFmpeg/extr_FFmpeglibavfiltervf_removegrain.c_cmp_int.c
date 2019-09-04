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
 int FFDIFFSIGN (int,int) ; 

__attribute__((used)) static int cmp_int(const void *p1, const void *p2)
{
    int left  = *(const int *)p1;
    int right = *(const int *)p2;
    return FFDIFFSIGN(left, right);
}