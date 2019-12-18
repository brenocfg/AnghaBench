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
struct bpf_d {scalar_t__ bd_hbuf_read; scalar_t__ bd_sbuf; scalar_t__ bd_hbuf; scalar_t__ bd_fbuf; scalar_t__ bd_filter; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
bpf_freed(struct bpf_d *d)
{
	/*
	 * We don't need to lock out interrupts since this descriptor has
	 * been detached from its interface and it yet hasn't been marked
	 * free.
	 */
	if (d->bd_hbuf_read != 0)
		panic("bpf buffer freed during read");

	if (d->bd_sbuf != 0) {
		FREE(d->bd_sbuf, M_DEVBUF);
		if (d->bd_hbuf != 0)
			FREE(d->bd_hbuf, M_DEVBUF);
		if (d->bd_fbuf != 0)
			FREE(d->bd_fbuf, M_DEVBUF);
	}
	if (d->bd_filter)
		FREE((caddr_t)d->bd_filter, M_DEVBUF);
}