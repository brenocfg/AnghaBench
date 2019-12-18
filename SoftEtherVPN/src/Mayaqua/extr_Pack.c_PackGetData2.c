#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int PackGetDataEx2 (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool PackGetData2(PACK *p, char *name, void *data, UINT size)
{
	return PackGetDataEx2(p, name, data, size, 0);
}