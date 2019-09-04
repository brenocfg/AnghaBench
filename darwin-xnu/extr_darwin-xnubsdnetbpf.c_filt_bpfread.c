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
struct knote {scalar_t__ kn_hook; } ;
struct bpf_d {int dummy; } ;

/* Variables and functions */
 int filt_bpfread_common (struct knote*,struct bpf_d*) ; 

__attribute__((used)) static int
filt_bpfread(struct knote *kn, long hint)
{
#pragma unused(hint)
	struct bpf_d *d = (struct bpf_d *)kn->kn_hook;

	return (filt_bpfread_common(kn, d));
}