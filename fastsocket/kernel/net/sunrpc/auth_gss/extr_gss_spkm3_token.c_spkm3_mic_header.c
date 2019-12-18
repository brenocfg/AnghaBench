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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 

void
spkm3_mic_header(unsigned char **hdrbuf, unsigned int *hdrlen, unsigned char *ctxdata, int elen, int zbit)
{
	char *hptr = *hdrbuf;
	char *top = *hdrbuf;

	*(u8 *)hptr++ = 0x30;
	*(u8 *)hptr++ = elen + 7;  /* on the wire header length */

	/* tokenid */
	*(u8 *)hptr++ = 0x02;
	*(u8 *)hptr++ = 0x02;
	*(u8 *)hptr++ = 0x01;
	*(u8 *)hptr++ = 0x01;

	/* coniextid */
	*(u8 *)hptr++ = 0x03;
	*(u8 *)hptr++ = elen + 1; /* add 1 to include zbit */
	*(u8 *)hptr++ = zbit;
	memcpy(hptr, ctxdata, elen);
	hptr += elen;
	*hdrlen = hptr - top;
}