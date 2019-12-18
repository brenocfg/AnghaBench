#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t rate; size_t dptr; int /*<<< orphan*/  A; scalar_t__ dbuf; } ;
typedef  TYPE_1__ br_shake_context ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  process_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xor_block (int /*<<< orphan*/ ,scalar_t__,size_t) ; 

void
br_shake_inject(br_shake_context *sc, const void *data, size_t len)
{
	const unsigned char *buf;
	size_t rate, dptr;

	buf = data;
	rate = sc->rate;
	dptr = sc->dptr;
	while (len > 0) {
		size_t clen;

		clen = rate - dptr;
		if (clen > len) {
			clen = len;
		}
		memcpy(sc->dbuf + dptr, buf, clen);
		dptr += clen;
		buf += clen;
		len -= clen;
		if (dptr == rate) {
			xor_block(sc->A, sc->dbuf, rate);
			process_block(sc->A);
			dptr = 0;
		}
	}
	sc->dptr = dptr;
}