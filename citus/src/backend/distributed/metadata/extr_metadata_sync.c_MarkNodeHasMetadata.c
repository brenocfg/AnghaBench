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
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_dist_node_hasmetadata ; 
 int /*<<< orphan*/  UpdateDistNodeBoolAttr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
MarkNodeHasMetadata(char *nodeName, int32 nodePort, bool hasMetadata)
{
	UpdateDistNodeBoolAttr(nodeName, nodePort,
						   Anum_pg_dist_node_hasmetadata,
						   hasMetadata);
}