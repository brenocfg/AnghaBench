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
 int /*<<< orphan*/  IS_ERR (struct tape_request*) ; 
 struct tape_request* __tape_3592_enable_crypt (struct tape_device*) ; 
 int /*<<< orphan*/  tape_do_io_async_free (struct tape_device*,struct tape_request*) ; 

__attribute__((used)) static void tape_3592_enable_crypt_async(struct tape_device *device)
{
	struct tape_request *request;

	request = __tape_3592_enable_crypt(device);
	if (!IS_ERR(request))
		tape_do_io_async_free(device, request);
}