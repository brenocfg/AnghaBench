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
struct nes_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nes_terminate_done (struct nes_qp*,int) ; 

__attribute__((used)) static void nes_terminate_timeout(unsigned long context)
{
	struct nes_qp *nesqp = (struct nes_qp *)(unsigned long)context;

	nes_terminate_done(nesqp, 1);
}