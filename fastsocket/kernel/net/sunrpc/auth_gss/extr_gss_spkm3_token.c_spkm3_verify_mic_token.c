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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_netobj {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_DEFECTIVE_TOKEN ; 
 int /*<<< orphan*/  decode_asn1_bitstring (struct xdr_netobj*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

u32
spkm3_verify_mic_token(unsigned char **tokp, int *mic_hdrlen, unsigned char **cksum)
{
	struct xdr_netobj       spkm3_ctx_id = {.len =0, .data = NULL};
	unsigned char 		*ptr = *tokp;
	int 			ctxelen;
	u32     		ret = GSS_S_DEFECTIVE_TOKEN;

	/* spkm3 innercontext token preamble */
	if ((ptr[0] != 0xa4) || (ptr[2] != 0x30)) {
		dprintk("RPC:       BAD SPKM ictoken preamble\n");
		goto out;
	}

	*mic_hdrlen = ptr[3];

	/* token type */
	if ((ptr[4] != 0x02) || (ptr[5] != 0x02)) {
		dprintk("RPC:       BAD asn1 SPKM3 token type\n");
		goto out;
	}

	/* only support SPKM_MIC_TOK */
	if((ptr[6] != 0x01) || (ptr[7] != 0x01)) {
		dprintk("RPC:       ERROR unsupported SPKM3 token \n");
		goto out;
	}

	/* contextid */
	if (ptr[8] != 0x03) {
		dprintk("RPC:       BAD SPKM3 asn1 context-id type\n");
		goto out;
	}

	ctxelen = ptr[9];
	if (ctxelen > 17) {  /* length includes asn1 zbit octet */
		dprintk("RPC:       BAD SPKM3 contextid len %d\n", ctxelen);
		goto out;
	}

	/* ignore ptr[10] */

	if(!decode_asn1_bitstring(&spkm3_ctx_id, &ptr[11], ctxelen - 1, 16))
		goto out;

	/*
	* in the current implementation: the optional int-alg is not present
	* so the default int-alg (md5) is used the optional snd-seq field is
	* also not present
	*/

	if (*mic_hdrlen != 6 + ctxelen) {
		dprintk("RPC:       BAD SPKM_ MIC_TOK header len %d: we only "
				"support default int-alg (should be absent) "
				"and do not support snd-seq\n", *mic_hdrlen);
		goto out;
	}
	/* checksum */
	*cksum = (&ptr[10] + ctxelen); /* ctxelen includes ptr[10] */

	ret = GSS_S_COMPLETE;
out:
	kfree(spkm3_ctx_id.data);
	return ret;
}