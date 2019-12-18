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
typedef  int /*<<< orphan*/  u16 ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nrdy (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_ready (struct r8a66597*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_irq_disable(struct r8a66597 *r8a66597, u16 pipenum)
{
	disable_irq_ready(r8a66597, pipenum);
	disable_irq_nrdy(r8a66597, pipenum);
}