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
struct bpf_d {int bd_traffic_class; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SO_VALID_TC (int) ; 

__attribute__((used)) static int
bpf_set_traffic_class(struct bpf_d *d, int tc)
{
	int error = 0;

	if (!SO_VALID_TC(tc))
		error = EINVAL;
	else
		d->bd_traffic_class = tc;

	return (error);
}