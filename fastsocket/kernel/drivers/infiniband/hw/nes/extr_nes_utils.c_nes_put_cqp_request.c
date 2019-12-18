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
struct nes_device {int dummy; } ;
struct nes_cqp_request {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_free_cqp_request (struct nes_device*,struct nes_cqp_request*) ; 

void nes_put_cqp_request(struct nes_device *nesdev,
			 struct nes_cqp_request *cqp_request)
{
	if (atomic_dec_and_test(&cqp_request->refcount))
		nes_free_cqp_request(nesdev, cqp_request);
}