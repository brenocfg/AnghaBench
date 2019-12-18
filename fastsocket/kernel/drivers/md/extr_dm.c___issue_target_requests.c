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
struct dm_target {int dummy; } ;
struct clone_info {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  __issue_target_request (struct clone_info*,struct dm_target*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __issue_target_requests(struct clone_info *ci, struct dm_target *ti,
				    unsigned num_requests, sector_t len)
{
	unsigned request_nr;

	for (request_nr = 0; request_nr < num_requests; request_nr++)
		__issue_target_request(ci, ti, request_nr, len);
}