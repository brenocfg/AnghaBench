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
typedef  int /*<<< orphan*/  io_return_t ;
typedef  int /*<<< orphan*/  io_req_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gprofstrategy ; 
 int /*<<< orphan*/  minphys ; 

io_return_t
gprofwrite(dev_t dev,
	   io_req_t ior)
{
	return (block_io(gprofstrategy, minphys, ior));
}