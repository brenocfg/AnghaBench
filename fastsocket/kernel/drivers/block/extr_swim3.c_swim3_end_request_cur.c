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

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_cur_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_req ; 
 int swim3_end_request (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool swim3_end_request_cur(int err)
{
	return swim3_end_request(err, blk_rq_cur_bytes(fd_req));
}