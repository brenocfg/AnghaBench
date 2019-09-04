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
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 

void countSort(char * oldArr, char * newArr)
{
    int count[26] = {0};
    int i;
    int lenOld = strlen(oldArr);
    memset(newArr, 0, lenOld); //clear
    int pos;
    for (i = 0; i < lenOld; i++)
    {
        pos = *(oldArr + i) - 'A';
        count[pos]++;
    }
    for (i = 0; i < 25; i++)
    {
        count[i + 1] += count[i];
    }
    for (i = 0; i < lenOld; i++)
    {
        pos = count[*(oldArr + i) - 'A'];
        while (newArr[pos - 1] != 0)
        {
            pos++;
        }
        newArr[pos - 1] = *(oldArr + i);
    }
}