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
struct ar9170 {int state; } ;
typedef  enum carl9170_device_state { ____Placeholder_carl9170_device_state } carl9170_device_state ;

/* Variables and functions */

__attribute__((used)) static inline void __carl9170_set_state(struct ar9170 *ar,
	enum carl9170_device_state newstate)
{
	ar->state = newstate;
}