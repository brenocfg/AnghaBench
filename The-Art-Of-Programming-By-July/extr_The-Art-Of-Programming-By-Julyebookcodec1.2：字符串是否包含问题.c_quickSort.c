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
 int partion1 (char*,int,int) ; 

void quickSort(char * arr, int start, int end)
{
    if (start < end)
    {
        int mid = partion1(arr, start, end);
        quickSort(arr, start, mid - 1);
        quickSort(arr, mid + 1, end);
    }
}