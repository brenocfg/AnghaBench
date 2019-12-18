#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_17__ {int sz_pool; int (* infunc ) (TYPE_1__*,uint8_t*,int) ;int nrst; int* inbuf; int width; int height; int msx; int msy; int* qtid; int* mcubuf; int* dptr; int dctr; int /*<<< orphan*/  dmsk; void* workbuf; scalar_t__* qttbl; scalar_t__** huffbits; scalar_t__** huffdata; scalar_t__** huffcode; void* device; void* pool; } ;
typedef  int /*<<< orphan*/  JRESULT ;
typedef  TYPE_1__ JDEC ;

/* Variables and functions */
 int /*<<< orphan*/  JDR_FMT1 ; 
 int /*<<< orphan*/  JDR_FMT3 ; 
 int /*<<< orphan*/  JDR_INP ; 
 int /*<<< orphan*/  JDR_MEM1 ; 
 int /*<<< orphan*/  JDR_MEM2 ; 
 int /*<<< orphan*/  JDR_OK ; 
 int /*<<< orphan*/  JDR_PAR ; 
 int JD_SZBUF ; 
 int LDB_WORD (int*) ; 
 void* alloc_pool (TYPE_1__*,int) ; 
 int /*<<< orphan*/  create_huffman_tbl (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  create_qt_tbl (TYPE_1__*,int*,int) ; 
 int stub1 (TYPE_1__*,int*,int) ; 
 int stub2 (TYPE_1__*,int*,int) ; 
 int stub3 (TYPE_1__*,int*,int) ; 
 int stub4 (TYPE_1__*,int*,int) ; 
 int stub5 (TYPE_1__*,int*,int) ; 
 int stub6 (TYPE_1__*,int*,int) ; 
 int stub7 (TYPE_1__*,int*,int) ; 
 int stub8 (TYPE_1__*,int*,int) ; 
 int stub9 (TYPE_1__*,int*,int) ; 

JRESULT jd_prepare (
	JDEC* jd,			/* Blank decompressor object */
	uint16_t (*infunc)(JDEC*, uint8_t*, uint16_t),	/* JPEG strem input function */
	void* pool,			/* Working buffer for the decompression session */
	uint16_t sz_pool,	/* Size of working buffer */
	void* dev			/* I/O device identifier for the session */
)
{
	uint8_t *seg, b;
	uint16_t marker;
	uint32_t ofs;
	uint16_t n, i, j, len;
	JRESULT rc;


	if (!pool) return JDR_PAR;

	jd->pool = pool;		/* Work memroy */
	jd->sz_pool = sz_pool;	/* Size of given work memory */
	jd->infunc = infunc;	/* Stream input function */
	jd->device = dev;		/* I/O device identifier */
	jd->nrst = 0;			/* No restart interval (default) */

	for (i = 0; i < 2; i++) {	/* Nulls pointers */
		for (j = 0; j < 2; j++) {
			jd->huffbits[i][j] = 0;
			jd->huffcode[i][j] = 0;
			jd->huffdata[i][j] = 0;
		}
	}
	for (i = 0; i < 4; jd->qttbl[i++] = 0) ;

	jd->inbuf = seg = alloc_pool(jd, JD_SZBUF);		/* Allocate stream input buffer */
	if (!seg) return JDR_MEM1;

	if (jd->infunc(jd, seg, 2) != 2) return JDR_INP;/* Check SOI marker */
	if (LDB_WORD(seg) != 0xFFD8) return JDR_FMT1;	/* Err: SOI is not detected */
	ofs = 2;

	for (;;) {
		/* Get a JPEG marker */
		if (jd->infunc(jd, seg, 4) != 4) return JDR_INP;
		marker = LDB_WORD(seg);		/* Marker */
		len = LDB_WORD(seg + 2);	/* Length field */
		if (len <= 2 || (marker >> 8) != 0xFF) return JDR_FMT1;
		len -= 2;		/* Content size excluding length field */
		ofs += 4 + len;	/* Number of bytes loaded */

		switch (marker & 0xFF) {
		case 0xC0:	/* SOF0 (baseline JPEG) */
			/* Load segment data */
			if (len > JD_SZBUF) return JDR_MEM2;
			if (jd->infunc(jd, seg, len) != len) return JDR_INP;

			jd->width = LDB_WORD(seg+3);		/* Image width in unit of pixel */
			jd->height = LDB_WORD(seg+1);		/* Image height in unit of pixel */
			if (seg[5] != 3) return JDR_FMT3;	/* Err: Supports only Y/Cb/Cr format */

			/* Check three image components */
			for (i = 0; i < 3; i++) {
				b = seg[7 + 3 * i];							/* Get sampling factor */
				if (!i) {	/* Y component */
					if (b != 0x11 && b != 0x22 && b != 0x21) {	/* Check sampling factor */
						return JDR_FMT3;					/* Err: Supports only 4:4:4, 4:2:0 or 4:2:2 */
					}
					jd->msx = b >> 4; jd->msy = b & 15;		/* Size of MCU [blocks] */
				} else {	/* Cb/Cr component */
					if (b != 0x11) return JDR_FMT3;			/* Err: Sampling factor of Cr/Cb must be 1 */
				}
				b = seg[8 + 3 * i];							/* Get dequantizer table ID for this component */
				if (b > 3) return JDR_FMT3;					/* Err: Invalid ID */
				jd->qtid[i] = b;
			}
			break;

		case 0xDD:	/* DRI */
			/* Load segment data */
			if (len > JD_SZBUF) return JDR_MEM2;
			if (jd->infunc(jd, seg, len) != len) return JDR_INP;

			/* Get restart interval (MCUs) */
			jd->nrst = LDB_WORD(seg);
			break;

		case 0xC4:	/* DHT */
			/* Load segment data */
			if (len > JD_SZBUF) return JDR_MEM2;
			if (jd->infunc(jd, seg, len) != len) return JDR_INP;

			/* Create huffman tables */
			rc = create_huffman_tbl(jd, seg, len);
			if (rc) return rc;
			break;

		case 0xDB:	/* DQT */
			/* Load segment data */
			if (len > JD_SZBUF) return JDR_MEM2;
			if (jd->infunc(jd, seg, len) != len) return JDR_INP;

			/* Create de-quantizer tables */
			rc = create_qt_tbl(jd, seg, len);
			if (rc) return rc;
			break;

		case 0xDA:	/* SOS */
			/* Load segment data */
			if (len > JD_SZBUF) return JDR_MEM2;
			if (jd->infunc(jd, seg, len) != len) return JDR_INP;

			if (!jd->width || !jd->height) return JDR_FMT1;	/* Err: Invalid image size */

			if (seg[0] != 3) return JDR_FMT3;				/* Err: Supports only three color components format */

			/* Check if all tables corresponding to each components have been loaded */
			for (i = 0; i < 3; i++) {
				b = seg[2 + 2 * i];	/* Get huffman table ID */
				if (b != 0x00 && b != 0x11)	return JDR_FMT3;	/* Err: Different table number for DC/AC element */
				b = i ? 1 : 0;
				if (!jd->huffbits[b][0] || !jd->huffbits[b][1]) {	/* Check dc/ac huffman table for this component */
					return JDR_FMT1;					/* Err: Nnot loaded */
				}
				if (!jd->qttbl[jd->qtid[i]]) {			/* Check dequantizer table for this component */
					return JDR_FMT1;					/* Err: Not loaded */
				}
			}

			/* Allocate working buffer for MCU and RGB */
			n = jd->msy * jd->msx;						/* Number of Y blocks in the MCU */
			if (!n) return JDR_FMT1;					/* Err: SOF0 has not been loaded */
			len = n * 64 * 2 + 64;						/* Allocate buffer for IDCT and RGB output */
			if (len < 256) len = 256;					/* but at least 256 byte is required for IDCT */
			jd->workbuf = alloc_pool(jd, len);			/* and it may occupy a part of following MCU working buffer for RGB output */
			if (!jd->workbuf) return JDR_MEM1;			/* Err: not enough memory */
			jd->mcubuf = (uint8_t*)alloc_pool(jd, (uint16_t)((n + 2) * 64));	/* Allocate MCU working buffer */
			if (!jd->mcubuf) return JDR_MEM1;			/* Err: not enough memory */

			/* Pre-load the JPEG data to extract it from the bit stream */
			jd->dptr = seg; jd->dctr = 0; jd->dmsk = 0;	/* Prepare to read bit stream */
			if (ofs %= JD_SZBUF) {						/* Align read offset to JD_SZBUF */
				jd->dctr = jd->infunc(jd, seg + ofs, (uint16_t)(JD_SZBUF - ofs));
				jd->dptr = seg + ofs - 1;
			}

			return JDR_OK;		/* Initialization succeeded. Ready to decompress the JPEG image. */

		case 0xC1:	/* SOF1 */
		case 0xC2:	/* SOF2 */
		case 0xC3:	/* SOF3 */
		case 0xC5:	/* SOF5 */
		case 0xC6:	/* SOF6 */
		case 0xC7:	/* SOF7 */
		case 0xC9:	/* SOF9 */
		case 0xCA:	/* SOF10 */
		case 0xCB:	/* SOF11 */
		case 0xCD:	/* SOF13 */
		case 0xCE:	/* SOF14 */
		case 0xCF:	/* SOF15 */
		case 0xD9:	/* EOI */
			return JDR_FMT3;	/* Unsuppoted JPEG standard (may be progressive JPEG) */

		default:	/* Unknown segment (comment, exif or etc..) */
			/* Skip segment data */
			if (jd->infunc(jd, 0, len) != len) {	/* Null pointer specifies to skip bytes of stream */
				return JDR_INP;
			}
		}
	}
}