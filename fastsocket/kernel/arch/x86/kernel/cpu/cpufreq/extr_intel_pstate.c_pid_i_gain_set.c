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
struct _pid {int /*<<< orphan*/  i_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  div_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_tofp (int) ; 

__attribute__((used)) static inline void pid_i_gain_set(struct _pid *pid, int percent)
{
	pid->i_gain = div_fp(int_tofp(percent), int_tofp(100));
}