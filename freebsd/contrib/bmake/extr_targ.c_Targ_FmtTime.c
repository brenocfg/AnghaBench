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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

char *
Targ_FmtTime(time_t tm)
{
    struct tm	  	*parts;
    static char	  	buf[128];

    parts = localtime(&tm);
    (void)strftime(buf, sizeof buf, "%k:%M:%S %b %d, %Y", parts);
    return(buf);
}