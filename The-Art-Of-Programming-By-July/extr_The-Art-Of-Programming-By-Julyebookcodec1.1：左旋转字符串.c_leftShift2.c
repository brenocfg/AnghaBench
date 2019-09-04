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

void leftShift2(char * arr, int len, int n)
{
    int i;
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
    /*
     *  not good O(k * (n + k)) k = tmpLen - p1
     for(i = 0;i < tmpLen - p1;i++){ //移动后面剩下的
     tmpChar = *(arr + tmpLen - 1);
     for(j = tmpLen - 1;j > p0;j--){
     *(arr + j) = *(arr + j -1);
     }
     *(arr + p0) = tmpChar;
     }
     */
    /* good O(k * n) */
    while (p1 < tmpLen)
    {
        tmpChar = *(arr + p1);
        for (i = p1; i > p0; i--)
        {
            *(arr + i) = *(arr + i - 1);
        }
        *(arr + p0) = tmpChar;
        p0++;
        p1++;
    }
}