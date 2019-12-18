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
typedef  int /*<<< orphan*/  gzFile ;

/* Variables and functions */
 int gzwrite (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 scalar_t__ strlen (char const*) ; 

int gzputs(gzFile file, const char *str)
{
    int ret;
    unsigned len;

    /* write string */
    len = (unsigned)strlen(str);
    ret = gzwrite(file, str, len);
    return ret == 0 && len != 0 ? -1 : ret;
}