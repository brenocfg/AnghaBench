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
 size_t strlen (char*) ; 

void leftShift1(char * arr, int n)
{
    size_t tmpLen = strlen(arr);
    char tmpChar;
    int i, j;
    if (n >= 0)
    {
        for (i = 0; i < n; i++)
        {
            tmpChar = *arr;
            for (j = 0; j < tmpLen - 1; j++)
            {
                *(arr + j) = *(arr + j + 1);
            }
            *(arr + tmpLen - 1) = tmpChar;
        }
    }
    else
    {
        for (i = 0; i < -n; i++)
        {
            tmpChar = *(arr + tmpLen - 1);
            for (j = tmpLen - 1; j > 0; j--)
            {
                *(arr + j) = *(arr + j - 1);
            }
            *arr = tmpChar;
        }
    }
}