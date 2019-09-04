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
 int gcd (int,int) ; 

void leftShift6(char * arr, int len, int n)
{
    int group = gcd(len, n);
    char tmpChar;
    int x = len / group;
    int i, j;
    for (i = 0; i < group; i++)
    {
        tmpChar = *(arr + i);
        for (j = 0; j < x - 1; j++)
        {
            *(arr + (i + (j * n)) % len) = *(arr + (i + (j * n) + n) % len);
        }
        *(arr + (i + (j * n)) % len) = tmpChar;
    }
}