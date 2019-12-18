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
struct bpf_d {scalar_t__ bd_hbuf_read; scalar_t__ bd_dcount; scalar_t__ bd_rcount; scalar_t__ bd_hcnt; scalar_t__ bd_scnt; scalar_t__ bd_hlen; scalar_t__ bd_slen; int /*<<< orphan*/ * bd_hbuf; int /*<<< orphan*/ * bd_fbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
reset_d(struct bpf_d *d)
{
	if (d->bd_hbuf_read != 0)
		panic("resetting buffers during read");

	if (d->bd_hbuf) {
		/* Free the hold buffer. */
		d->bd_fbuf = d->bd_hbuf;
		d->bd_hbuf = NULL;
	}
	d->bd_slen = 0;
	d->bd_hlen = 0;
	d->bd_scnt = 0;
	d->bd_hcnt = 0;
	d->bd_rcount = 0;
	d->bd_dcount = 0;
}