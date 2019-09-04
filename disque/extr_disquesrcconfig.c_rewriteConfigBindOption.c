#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rewriteConfigState {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {scalar_t__ bindaddr_count; int /*<<< orphan*/  bindaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rewriteConfigMarkAsProcessed (struct rewriteConfigState*,char*) ; 
 int /*<<< orphan*/  rewriteConfigRewriteLine (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatsds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsjoin (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_1__ server ; 

void rewriteConfigBindOption(struct rewriteConfigState *state) {
    int force = 1;
    sds line, addresses;
    char *option = "bind";

    /* Nothing to rewrite if we don't have bind addresses. */
    if (server.bindaddr_count == 0) {
        rewriteConfigMarkAsProcessed(state,option);
        return;
    }

    /* Rewrite as bind <addr1> <addr2> ... <addrN> */
    addresses = sdsjoin(server.bindaddr,server.bindaddr_count," ");
    line = sdsnew(option);
    line = sdscatlen(line, " ", 1);
    line = sdscatsds(line, addresses);
    sdsfree(addresses);

    rewriteConfigRewriteLine(state,option,line,force);
}