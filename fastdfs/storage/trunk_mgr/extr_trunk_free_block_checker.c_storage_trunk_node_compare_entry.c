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
struct TYPE_2__ {int /*<<< orphan*/  trunk_file_id; } ;
typedef  TYPE_1__ FDFSTrunksById ;
typedef  int /*<<< orphan*/  FDFSTrunkFileIdentifier ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int storage_trunk_node_compare_entry(void *p1, void *p2)
{
	return memcmp(&(((FDFSTrunksById *)p1)->trunk_file_id), \
			&(((FDFSTrunksById *)p2)->trunk_file_id), \
			sizeof(FDFSTrunkFileIdentifier));
}