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

int partion1(char * arr, int start, int end)
{
    char tmpChar;
    int i;
    while (*(arr + start) <= *(arr + end) && start < end)
    {
        start++; //start 指向第一个大的数据
    }
    if (start == end)
    {
        return start; //已经有序
    }
    for (i = start + 1; i < end; i++)
    {
        if (*(arr + i) < * (arr + end)) //交换
        {
            tmpChar = *(arr + start);
            *(arr + start) = *(arr + i);
            *(arr + i) = tmpChar;
            start++;
        }
    }
    tmpChar = *(arr + start);
    *(arr + start) = *(arr + i);
    *(arr + i) = tmpChar;
    return start;
}