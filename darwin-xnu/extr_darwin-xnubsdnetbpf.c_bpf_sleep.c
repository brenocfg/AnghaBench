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
typedef  int /*<<< orphan*/  u_int64_t ;
struct bpf_d {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  bpf_mlock ; 
 int /*<<< orphan*/  clock_interval_to_deadline (int,int,int /*<<< orphan*/ *) ; 
 int hz ; 
 int msleep1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bpf_sleep(struct bpf_d *d, int pri, const char *wmesg, int timo)
{
	u_int64_t abstime = 0;

	if (timo != 0)
		clock_interval_to_deadline(timo, NSEC_PER_SEC / hz, &abstime);

	return (msleep1((caddr_t)d, bpf_mlock, pri, wmesg, abstime));
}