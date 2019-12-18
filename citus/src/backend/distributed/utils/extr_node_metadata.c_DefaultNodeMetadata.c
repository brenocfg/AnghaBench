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
struct TYPE_3__ {int shouldHaveShards; int /*<<< orphan*/  groupId; int /*<<< orphan*/  nodeRack; } ;
typedef  TYPE_1__ NodeMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_GROUP_ID ; 
 int /*<<< orphan*/  WORKER_DEFAULT_RACK ; 

__attribute__((used)) static NodeMetadata
DefaultNodeMetadata()
{
	NodeMetadata nodeMetadata = {
		.nodeRack = WORKER_DEFAULT_RACK,
		.shouldHaveShards = true,
		.groupId = INVALID_GROUP_ID,
	};
	return nodeMetadata;
}