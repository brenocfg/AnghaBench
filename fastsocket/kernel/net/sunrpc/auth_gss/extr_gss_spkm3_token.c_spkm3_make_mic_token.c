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
struct xdr_netobj {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

void
spkm3_make_mic_token(unsigned char **tokp, int toklen, struct xdr_netobj *mic_hdr, struct xdr_netobj *md5cksum, int md5elen, int md5zbit)
{
	unsigned char *ict = *tokp;

	*(u8 *)ict++ = 0xa4;
	*(u8 *)ict++ = toklen;
	memcpy(ict, mic_hdr->data, mic_hdr->len);
	ict += mic_hdr->len;

	*(u8 *)ict++ = 0x03;
	*(u8 *)ict++ = md5elen + 1; /* add 1 to include zbit */
	*(u8 *)ict++ = md5zbit;
	memcpy(ict, md5cksum->data, md5elen);
}