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
struct tape_request {int dummy; } ;
struct tape_device {int dummy; } ;

/* Variables and functions */
 int tape_do_io (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  tape_free_request (struct tape_request*) ; 

__attribute__((used)) static inline int
tape_do_io_free(struct tape_device *device, struct tape_request *request)
{
	int rc;

	rc = tape_do_io(device, request);
	tape_free_request(request);
	return rc;
}