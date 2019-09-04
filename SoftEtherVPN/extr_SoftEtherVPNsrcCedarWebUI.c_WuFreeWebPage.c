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
struct TYPE_4__ {struct TYPE_4__* data; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ WU_WEBPAGE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeHttpHeader (int /*<<< orphan*/ ) ; 

void WuFreeWebPage(WU_WEBPAGE *page)
{
	if(page == NULL)
	{
		return;
	}

	FreeHttpHeader(page->header);
	Free(page->data);
	Free(page);
}