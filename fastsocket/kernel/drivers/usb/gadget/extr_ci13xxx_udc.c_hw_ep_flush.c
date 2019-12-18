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
 int /*<<< orphan*/  CAP_ENDPTFLUSH ; 
 int /*<<< orphan*/  CAP_ENDPTSTAT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ hw_cread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_cwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hw_ep_bit (int,int) ; 

__attribute__((used)) static int hw_ep_flush(int num, int dir)
{
	int n = hw_ep_bit(num, dir);

	do {
		/* flush any pending transfer */
		hw_cwrite(CAP_ENDPTFLUSH, BIT(n), BIT(n));
		while (hw_cread(CAP_ENDPTFLUSH, BIT(n)))
			cpu_relax();
	} while (hw_cread(CAP_ENDPTSTAT, BIT(n)));

	return 0;
}