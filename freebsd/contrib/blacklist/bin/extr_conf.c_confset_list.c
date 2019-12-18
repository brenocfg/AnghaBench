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
struct confset {size_t cs_n; int /*<<< orphan*/ * cs_c; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 char const* conf_print (char*,int,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lfun (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void
confset_list(const struct confset *cs, const char *msg, const char *where)
{
	char buf[BUFSIZ];

	(*lfun)(LOG_DEBUG, "[%s]", msg);
	(*lfun)(LOG_DEBUG, "%20.20s\ttype\tproto\towner\tname\tnfail\tduration",
	    where);
	for (size_t i = 0; i < cs->cs_n; i++)
		(*lfun)(LOG_DEBUG, "%s", conf_print(buf, sizeof(buf), "", "\t",
		    &cs->cs_c[i]));
}