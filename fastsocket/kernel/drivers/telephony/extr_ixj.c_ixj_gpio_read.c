#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_7__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_8__ {TYPE_1__ bytes; } ;
struct TYPE_10__ {TYPE_3__ ssr; TYPE_2__ gpio; } ;
typedef  TYPE_4__ IXJ ;

/* Variables and functions */
 scalar_t__ ixj_WriteDSPCommand (int,TYPE_4__*) ; 

__attribute__((used)) static inline int ixj_gpio_read(IXJ *j)
{
	if (ixj_WriteDSPCommand(0x5143, j))
		return -1;

	j->gpio.bytes.low = j->ssr.low;
	j->gpio.bytes.high = j->ssr.high;

	return 0;
}