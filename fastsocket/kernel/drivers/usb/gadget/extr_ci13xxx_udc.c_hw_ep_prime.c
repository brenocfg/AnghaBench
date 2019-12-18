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

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CAP_ENDPTPRIME ; 
 int /*<<< orphan*/  CAP_ENDPTSETUPSTAT ; 
 int EAGAIN ; 
 int EBUSY ; 
 int RX ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ hw_cread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_cwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hw_ep_bit (int,int) ; 
 scalar_t__ hw_ep_is_primed (int,int) ; 

__attribute__((used)) static int hw_ep_prime(int num, int dir, int is_ctrl)
{
	int n = hw_ep_bit(num, dir);

	/* the caller should flush first */
	if (hw_ep_is_primed(num, dir))
		return -EBUSY;

	if (is_ctrl && dir == RX && hw_cread(CAP_ENDPTSETUPSTAT, BIT(num)))
		return -EAGAIN;

	hw_cwrite(CAP_ENDPTPRIME, BIT(n), BIT(n));

	while (hw_cread(CAP_ENDPTPRIME, BIT(n)))
		cpu_relax();
	if (is_ctrl && dir == RX  && hw_cread(CAP_ENDPTSETUPSTAT, BIT(num)))
		return -EAGAIN;

	/* status shoult be tested according with manual but it doesn't work */
	return 0;
}