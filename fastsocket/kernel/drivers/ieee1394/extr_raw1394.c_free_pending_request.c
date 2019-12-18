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
struct pending_request {int /*<<< orphan*/  packet; struct pending_request* data; scalar_t__ free_data; struct pending_request* ibs; int /*<<< orphan*/  data_size; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpsb_free_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iso_buffer_size ; 
 int /*<<< orphan*/  kfree (struct pending_request*) ; 

__attribute__((used)) static void free_pending_request(struct pending_request *req)
{
	if (req->ibs) {
		if (atomic_dec_and_test(&req->ibs->refcount)) {
			atomic_sub(req->ibs->data_size, &iso_buffer_size);
			kfree(req->ibs);
		}
	} else if (req->free_data) {
		kfree(req->data);
	}
	hpsb_free_packet(req->packet);
	kfree(req);
}