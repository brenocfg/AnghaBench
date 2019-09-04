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
 int /*<<< orphan*/  leftShift2 (char*,int,int) ; 

void leftShift3(char * arr, int len, int n)
{
    size_t tmpLen = len;
    int p0 = 0;
    int p1 = n;
    char tmpChar;
    /*  O(m - n - k)  k is the last section*/
    while (p1 + n - 1 < tmpLen)
    {
        tmpChar = *(arr + p0);
        *(arr + p0) = *(arr + p1);
        *(arr + p1) = tmpChar;
        p0++;
        p1++;
    }
    if (p1 < tmpLen)
    {
        leftShift2(arr + p0, len - p0, n);
    }
}