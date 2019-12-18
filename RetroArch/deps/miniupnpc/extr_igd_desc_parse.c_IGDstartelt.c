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
struct TYPE_2__ {char* controlurl; char* eventsuburl; char* scpdurl; char* servicetype; } ;
struct IGDdatas {char* cureltname; TYPE_1__ tmp; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int MINIUPNPC_URL_MAXSIZE ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

void IGDstartelt(void * d, const char * name, int l)
{
	struct IGDdatas * datas = (struct IGDdatas *)d;
	if(l >= MINIUPNPC_URL_MAXSIZE)
		l = MINIUPNPC_URL_MAXSIZE-1;
	memcpy(datas->cureltname, name, l);
	datas->cureltname[l] = '\0';
	datas->level++;
	if( (l==7) && !memcmp(name, "service", l) ) {
		datas->tmp.controlurl[0] = '\0';
		datas->tmp.eventsuburl[0] = '\0';
		datas->tmp.scpdurl[0] = '\0';
		datas->tmp.servicetype[0] = '\0';
	}
}