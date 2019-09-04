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

int partion(char * arr, int start, int end)
{
    char tmpChar = *(arr + start);
    while (start < end)
    {
        while (*(arr + end) >= tmpChar && end > start)
        {
            end--;
        }
        if (start < end)
        {
            *(arr + start) = *(arr + end); //小的往左走
            start++;
        }
        else
        {
            break;
        }
        while (*(arr + start) <= tmpChar && end > start)
        {
            start++;
        }
        if (start < end)
        {
            *(arr + end) = *(arr + start);
            end--;
        }
        else
        {
            break;
        }
    }
    *(arr + start) = tmpChar;
    return start;
}