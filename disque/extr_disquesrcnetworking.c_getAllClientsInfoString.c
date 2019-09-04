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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_2__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  catClientInfoString (int /*<<< orphan*/ ,int) ; 
 int client ; 
 int listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsMakeRoomFor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 TYPE_1__ server ; 

sds getAllClientsInfoString(void) {
    listNode *ln;
    listIter li;
    client *client;
    sds o = sdsempty();

    o = sdsMakeRoomFor(o,200*listLength(server.clients));
    listRewind(server.clients,&li);
    while ((ln = listNext(&li)) != NULL) {
        client = listNodeValue(ln);
        o = catClientInfoString(o,client);
        o = sdscatlen(o,"\n",1);
    }
    return o;
}