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
struct gru_context_configuration_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unlock_handle (struct gru_context_configuration_handle*) ; 

__attribute__((used)) static inline void unlock_cch_handle(struct gru_context_configuration_handle
				     *cch)
{
	__unlock_handle(cch);
}