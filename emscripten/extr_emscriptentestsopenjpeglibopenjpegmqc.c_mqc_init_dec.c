#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* start; unsigned char* end; unsigned char* bp; int c; int ct; int a; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mqc_bytein (TYPE_1__*) ; 
 int /*<<< orphan*/  mqc_setcurctx (TYPE_1__*,int /*<<< orphan*/ ) ; 

void mqc_init_dec(opj_mqc_t *mqc, unsigned char *bp, int len) {
	mqc_setcurctx(mqc, 0);
	mqc->start = bp;
	mqc->end = bp + len;
	mqc->bp = bp;
	if (len==0) mqc->c = 0xff << 16;
	else mqc->c = *mqc->bp << 16;

#ifdef MQC_PERF_OPT
	{
		unsigned int c;
		unsigned int *ip;
		unsigned char *end = mqc->end - 1;
		mqc->buffer = opj_realloc(mqc->buffer, (2 * len + 1) * sizeof(unsigned int));
		ip = (unsigned int *) mqc->buffer;

		while (bp != end) {
			c = *(bp + 1);
			if (*bp == 0xff) {
				if (c > 0x8f) {
					*ip = 0x0000ff18;
				} else {
					bp++;
					*ip = 0x00000017 | (c << 9);
				}
			} else {
				bp++;
				*ip = 0x00000018 | (c << 8);
			}
			ip++;
		}

		/* Handle last byte of data */
		c = 0xff;
		if (*bp == 0xff) {
			*ip = 0x0000ff18;
		} else {
			bp++;
			*ip = 0x00000018 | (c << 8);
		}
		ip++;

		*ip = 0x0000ff08;
		mqc->bp = mqc->buffer;
	}
#endif
	mqc_bytein(mqc);
	mqc->c <<= 7;
	mqc->ct -= 7;
	mqc->a = 0x8000;
}