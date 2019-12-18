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
struct bbc_fan_control {int dummy; } ;

/* Variables and functions */
 int maybe_new_ambient_fan_speed (struct bbc_fan_control*) ; 
 int maybe_new_cpu_fan_speed (struct bbc_fan_control*) ; 
 int /*<<< orphan*/  set_fan_speeds (struct bbc_fan_control*) ; 

__attribute__((used)) static void maybe_new_fan_speeds(struct bbc_fan_control *fp)
{
	int new;

	new  = maybe_new_ambient_fan_speed(fp);
	new |= maybe_new_cpu_fan_speed(fp);

	if (new)
		set_fan_speeds(fp);
}