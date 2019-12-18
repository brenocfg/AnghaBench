#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  confLink; } ;
typedef  TYPE_1__ OrbisGlobalConf ;

/* Variables and functions */
 TYPE_1__* myConf ; 
 int /*<<< orphan*/  ps4LinkFinish () ; 
 int ps4LinkInitWithConf (int /*<<< orphan*/ ) ; 
 int rarch_main (int,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceSystemServiceHideSplashScreen () ; 
 int /*<<< orphan*/  sscanf (char*,char*,uintptr_t*) ; 

int main(int argc, char *argv[])
{
   int ret;

   sceSystemServiceHideSplashScreen();

	uintptr_t intptr=0;
	sscanf(argv[1],"%p",&intptr);
	myConf=(OrbisGlobalConf *)intptr;
	ret=ps4LinkInitWithConf(myConf->confLink);
	if(!ret)
	{
		ps4LinkFinish();
		return -1;
	}

   return rarch_main(argc, argv, NULL);
}