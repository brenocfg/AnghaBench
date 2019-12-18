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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_2__ {int (* MakeDirW ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* os ; 
 int stub1 (int /*<<< orphan*/ *) ; 

bool OSMakeDirW(wchar_t *name)
{
	return os->MakeDirW(name);
}