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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__** qttbl; } ;
typedef  TYPE_1__ JDEC ;

/* Variables and functions */
 int IPSF (int) ; 
 int JDR_FMT1 ; 
 int JDR_MEM1 ; 
 int JDR_OK ; 
 int ZIG (int) ; 
 scalar_t__* alloc_pool (TYPE_1__*,int) ; 

__attribute__((used)) static int create_qt_tbl (	/* 0:OK, !0:Failed */
	JDEC* jd,				/* Pointer to the decompressor object */
	const uint8_t* data,	/* Pointer to the quantizer tables */
	uint16_t ndata			/* Size of input data */
)
{
	uint16_t i;
	uint8_t d, z;
	int32_t *pb;


	while (ndata) {	/* Process all tables in the segment */
		if (ndata < 65) return JDR_FMT1;	/* Err: table size is unaligned */
		ndata -= 65;
		d = *data++;							/* Get table property */
		if (d & 0xF0) return JDR_FMT1;			/* Err: not 8-bit resolution */
		i = d & 3;								/* Get table ID */
		pb = alloc_pool(jd, 64 * sizeof (int32_t));/* Allocate a memory block for the table */
		if (!pb) return JDR_MEM1;				/* Err: not enough memory */
		jd->qttbl[i] = pb;						/* Register the table */
		for (i = 0; i < 64; i++) {				/* Load the table */
			z = ZIG(i);							/* Zigzag-order to raster-order conversion */
			pb[z] = (int32_t)((uint32_t)*data++ * IPSF(z));	/* Apply scale factor of Arai algorithm to the de-quantizers */
		}
	}

	return JDR_OK;
}