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
struct at91_cf_socket {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  det_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int at91_cf_present(struct at91_cf_socket *cf)
{
	return !gpio_get_value(cf->board->det_pin);
}