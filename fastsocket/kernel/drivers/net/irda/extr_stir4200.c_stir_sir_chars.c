#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stir_cb {int /*<<< orphan*/  rx_buff; TYPE_1__* netdev; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_unwrap_char (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void stir_sir_chars(struct stir_cb *stir,
			    const __u8 *bytes, int len)
{
	int i;

	for (i = 0; i < len; i++)
		async_unwrap_char(stir->netdev, &stir->netdev->stats,
				  &stir->rx_buff, bytes[i]);
}