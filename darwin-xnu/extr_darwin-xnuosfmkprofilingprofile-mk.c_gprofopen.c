#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  io_return_t ;
typedef  TYPE_1__* io_req_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_3__ {int /*<<< orphan*/  io_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SUCCESS ; 

io_return_t
gprofopen(dev_t dev,
	  int flags,
	  io_req_t ior)
{
	ior->io_error = D_SUCCESS;
	return(0);
}