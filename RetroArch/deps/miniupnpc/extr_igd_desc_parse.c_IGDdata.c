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
struct TYPE_2__ {char* servicetype; char* controlurl; char* eventsuburl; char* scpdurl; } ;
struct IGDdatas {char* urlbase; char* presentationurl; TYPE_1__ tmp; int /*<<< orphan*/  cureltname; } ;

/* Variables and functions */
 int MINIUPNPC_URL_MAXSIZE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

void IGDdata(void * d, const char * data, int l)
{
	struct IGDdatas * datas = (struct IGDdatas *)d;
	char * dstmember = 0;
	/*printf("%2d %s : %.*s\n",
           datas->level, datas->cureltname, l, data);	*/
	if( !strcmp(datas->cureltname, "URLBase") )
		dstmember = datas->urlbase;
	else if( !strcmp(datas->cureltname, "presentationURL") )
		dstmember = datas->presentationurl;
	else if( !strcmp(datas->cureltname, "serviceType") )
		dstmember = datas->tmp.servicetype;
	else if( !strcmp(datas->cureltname, "controlURL") )
		dstmember = datas->tmp.controlurl;
	else if( !strcmp(datas->cureltname, "eventSubURL") )
		dstmember = datas->tmp.eventsuburl;
	else if( !strcmp(datas->cureltname, "SCPDURL") )
		dstmember = datas->tmp.scpdurl;
/*	else if( !strcmp(datas->cureltname, "deviceType") )
		dstmember = datas->devicetype_tmp;*/
	if(dstmember)
	{
		if(l>=MINIUPNPC_URL_MAXSIZE)
			l = MINIUPNPC_URL_MAXSIZE-1;
		memcpy(dstmember, data, l);
		dstmember[l] = '\0';
	}
}