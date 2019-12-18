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
struct irb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int tape_3590_erp_basic (struct tape_device*,struct tape_request*,struct irb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tape_3590_erp_special_interrupt(struct tape_device *device,
				struct tape_request *request, struct irb *irb)
{
	return tape_3590_erp_basic(device, request, irb, -EIO);
}