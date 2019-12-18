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
struct TYPE_3__ {int max_count; scalar_t__ init_count; scalar_t__ count; scalar_t__ attr; } ;
typedef  TYPE_1__ ee_sema_t ;

/* Variables and functions */
 int CreateSema (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteSema (int) ; 
 scalar_t__ UI_is_active ; 
 int /*<<< orphan*/  WaitSema (int) ; 
 int /*<<< orphan*/  iSignalSema (int) ; 

void PLATFORM_Sleep(double s)
{

	if (UI_is_active){
	        int i,ret;
	        for (i=0;i<s * 100.0;i++){
	
			ee_sema_t sema;
	                sema.attr = 0;
	                sema.count = 0;
	                sema.init_count = 0;
	                sema.max_count = 1;
	                ret = CreateSema(&sema);
	                if (ret <= 0) {
	                        //could not create sema, strange!  continue anyway.
	                        return;
	                }
	
	                iSignalSema(ret);
	                WaitSema(ret);
	                DeleteSema(ret);
	        }
	}
}