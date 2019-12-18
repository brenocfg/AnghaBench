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
struct mixart_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXART_BA1_BRUTAL_RESET_OFFSET ; 
 int /*<<< orphan*/  MIXART_REG (struct mixart_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_be (int,int /*<<< orphan*/ ) ; 

void snd_mixart_reset_board(struct mixart_mgr *mgr)
{
	/* reset miXart */
	writel_be( 1, MIXART_REG(mgr, MIXART_BA1_BRUTAL_RESET_OFFSET) );
	return;
}