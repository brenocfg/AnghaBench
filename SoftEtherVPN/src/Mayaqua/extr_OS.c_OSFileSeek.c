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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int (* FileSeek ) (void*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_1__* os ; 
 int stub1 (void*,int /*<<< orphan*/ ,int) ; 

bool OSFileSeek(void *pData, UINT mode, int offset)
{
	return os->FileSeek(pData, mode, offset);
}