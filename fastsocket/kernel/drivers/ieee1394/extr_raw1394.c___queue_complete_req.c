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
struct pending_request {int /*<<< orphan*/  list; struct file_info* file_info; } ;
struct file_info {int /*<<< orphan*/  wait_complete; int /*<<< orphan*/  req_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __queue_complete_req(struct pending_request *req)
{
	struct file_info *fi = req->file_info;

	list_move_tail(&req->list, &fi->req_complete);
 	wake_up(&fi->wait_complete);
}