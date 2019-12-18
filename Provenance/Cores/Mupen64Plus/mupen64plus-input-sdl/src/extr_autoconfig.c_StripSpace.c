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
 int strlen (char*) ; 

__attribute__((used)) static char *StripSpace(char *pIn)
{
    char *pEnd = pIn + strlen(pIn) - 1;

    while (*pIn == ' ' || *pIn == '\t' || *pIn == '\r' || *pIn == '\n')
        pIn++;

    while (pIn <= pEnd && (*pEnd == ' ' || *pEnd == '\t' || *pEnd == '\r' || *pEnd == '\n'))
        *pEnd-- = 0;

    return pIn;
}