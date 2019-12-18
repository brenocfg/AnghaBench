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
typedef  int u_int ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static void
sprint_d(u_int n, char *buf, int buflen)
{	char dbuf[IFNAMSIZ];
	char *cp = dbuf+IFNAMSIZ-1;

        *cp = 0;
        do {	buflen--;
		cp--;
                *cp = "0123456789"[n % 10];
                n /= 10;
        } while (n != 0 && buflen > 0);
	strlcpy(buf, cp, IFNAMSIZ-buflen);
        return;
}