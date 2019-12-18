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
struct TYPE_2__ {int /*<<< orphan*/  sync; } ;
struct blizzard_request {TYPE_1__ par; } ;

/* Variables and functions */
 int REQ_COMPLETE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sync_handler(struct blizzard_request *req)
{
	complete(req->par.sync);
	return REQ_COMPLETE;
}