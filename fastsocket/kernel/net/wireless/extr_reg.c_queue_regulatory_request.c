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
struct regulatory_request {int /*<<< orphan*/  list; void** alpha2; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_requests_list ; 
 int /*<<< orphan*/  reg_requests_lock ; 
 int /*<<< orphan*/  reg_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* toupper (void*) ; 

__attribute__((used)) static void queue_regulatory_request(struct regulatory_request *request)
{
	request->alpha2[0] = toupper(request->alpha2[0]);
	request->alpha2[1] = toupper(request->alpha2[1]);

	spin_lock(&reg_requests_lock);
	list_add_tail(&request->list, &reg_requests_list);
	spin_unlock(&reg_requests_lock);

	schedule_work(&reg_work);
}