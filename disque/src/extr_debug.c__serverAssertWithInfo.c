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
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  _serverAssert (char*,char*,int) ; 
 int /*<<< orphan*/  _serverAssertPrintClientInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _serverAssertPrintObject (int /*<<< orphan*/ *) ; 

void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line) {
    if (c) _serverAssertPrintClientInfo(c);
    if (o) _serverAssertPrintObject(o);
    _serverAssert(estr,file,line);
}