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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {size_t dptr; size_t rate; unsigned char* dbuf; int /*<<< orphan*/ * A; } ;
typedef  TYPE_1__ br_shake_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc64le (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  process_block (int /*<<< orphan*/ *) ; 

void
br_shake_produce(br_shake_context *sc, void *out, size_t len)
{
	unsigned char *buf;
	size_t dptr, rate;

	buf = out;
	dptr = sc->dptr;
	rate = sc->rate;
	while (len > 0) {
		size_t clen;

		if (dptr == rate) {
			unsigned char *dbuf;
			uint64_t *A;

			A = sc->A;
			dbuf = sc->dbuf;
			process_block(A);
			br_enc64le(dbuf +   0,  A[ 0]);
			br_enc64le(dbuf +   8, ~A[ 1]);
			br_enc64le(dbuf +  16, ~A[ 2]);
			br_enc64le(dbuf +  24,  A[ 3]);
			br_enc64le(dbuf +  32,  A[ 4]);
			br_enc64le(dbuf +  40,  A[ 5]);
			br_enc64le(dbuf +  48,  A[ 6]);
			br_enc64le(dbuf +  56,  A[ 7]);
			br_enc64le(dbuf +  64, ~A[ 8]);
			br_enc64le(dbuf +  72,  A[ 9]);
			br_enc64le(dbuf +  80,  A[10]);
			br_enc64le(dbuf +  88,  A[11]);
			br_enc64le(dbuf +  96, ~A[12]);
			br_enc64le(dbuf + 104,  A[13]);
			br_enc64le(dbuf + 112,  A[14]);
			br_enc64le(dbuf + 120,  A[15]);
			br_enc64le(dbuf + 128,  A[16]);
			br_enc64le(dbuf + 136, ~A[17]);
			br_enc64le(dbuf + 144,  A[18]);
			br_enc64le(dbuf + 152,  A[19]);
			br_enc64le(dbuf + 160, ~A[20]);
			br_enc64le(dbuf + 168,  A[21]);
			br_enc64le(dbuf + 176,  A[22]);
			br_enc64le(dbuf + 184,  A[23]);
			br_enc64le(dbuf + 192,  A[24]);
			dptr = 0;
		}
		clen = rate - dptr;
		if (clen > len) {
			clen = len;
		}
		memcpy(buf, sc->dbuf + dptr, clen);
		dptr += clen;
		buf += clen;
		len -= clen;
	}
	sc->dptr = dptr;
}