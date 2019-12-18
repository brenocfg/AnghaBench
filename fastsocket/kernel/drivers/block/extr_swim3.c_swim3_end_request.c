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
 scalar_t__ __blk_end_request (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/ * fd_req ; 

__attribute__((used)) static bool swim3_end_request(int err, unsigned int nr_bytes)
{
	if (__blk_end_request(fd_req, err, nr_bytes))
		return true;

	fd_req = NULL;
	return false;
}