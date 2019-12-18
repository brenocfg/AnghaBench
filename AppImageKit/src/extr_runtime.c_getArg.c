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

char* getArg(int argc, char *argv[],char chr)
{
    int i;
    for (i=1; i<argc; ++i)
        if ((argv[i][0]=='-') && (argv[i][1]==chr))
            return &(argv[i][2]);
        return NULL;
}