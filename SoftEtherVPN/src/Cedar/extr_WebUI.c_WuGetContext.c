#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ExpireDate; } ;
typedef  TYPE_1__ WU_CONTEXT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 TYPE_1__* StrMapSearch (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ Tick64 () ; 
 scalar_t__ WU_CONTEXT_EXPIRE ; 

__attribute__((used)) static WU_CONTEXT *WuGetContext(LIST *contexts, char *sessionkey)
{
	WU_CONTEXT *ret = StrMapSearch(contexts, sessionkey);
	if(ret != NULL)
	{
		ret->ExpireDate = Tick64() + WU_CONTEXT_EXPIRE;
	}
	return ret;
}