#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int* dptr; int dctr; int* inbuf; int (* infunc ) (TYPE_1__*,int*,int /*<<< orphan*/ ) ;scalar_t__* dcv; scalar_t__ dmsk; } ;
typedef  int /*<<< orphan*/  JRESULT ;
typedef  TYPE_1__ JDEC ;

/* Variables and functions */
 int /*<<< orphan*/  JDR_FMT1 ; 
 int /*<<< orphan*/  JDR_INP ; 
 int /*<<< orphan*/  JDR_OK ; 
 int /*<<< orphan*/  JD_SZBUF ; 
 int stub1 (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JRESULT restart (
	JDEC* jd,		/* Pointer to the decompressor object */
	uint16_t rstn	/* Expected restert sequense number */
)
{
	uint16_t i, dc;
	uint16_t d;
	uint8_t *dp;


	/* Discard padding bits and get two bytes from the input stream */
	dp = jd->dptr; dc = jd->dctr;
	d = 0;
	for (i = 0; i < 2; i++) {
		if (!dc) {	/* No input data is available, re-fill input buffer */
			dp = jd->inbuf;
			dc = jd->infunc(jd, dp, JD_SZBUF);
			if (!dc) return JDR_INP;
		} else {
			dp++;
		}
		dc--;
		d = (d << 8) | *dp;	/* Get a byte */
	}
	jd->dptr = dp; jd->dctr = dc; jd->dmsk = 0;

	/* Check the marker */
	if ((d & 0xFFD8) != 0xFFD0 || (d & 7) != (rstn & 7)) {
		return JDR_FMT1;	/* Err: expected RSTn marker is not detected (may be collapted data) */
	}

	/* Reset DC offset */
	jd->dcv[2] = jd->dcv[1] = jd->dcv[0] = 0;

	return JDR_OK;
}