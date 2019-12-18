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
struct TYPE_2__ {int id; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  FDFSTrunkPathInfo ;
typedef  TYPE_1__ FDFSTrunkFileIdInfo ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int storage_compare_trunk_id_info(void *p1, void *p2)
{
	int result;
	result = memcmp(&(((FDFSTrunkFileIdInfo *)p1)->path), \
			&(((FDFSTrunkFileIdInfo *)p2)->path), \
			sizeof(FDFSTrunkPathInfo));
	if (result != 0)
	{
		return result;
	}

	return ((FDFSTrunkFileIdInfo *)p1)->id - ((FDFSTrunkFileIdInfo *)p2)->id;
}