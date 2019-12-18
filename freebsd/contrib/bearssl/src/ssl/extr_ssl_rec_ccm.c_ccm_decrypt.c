#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_5__ {int tag_len; void* iv; TYPE_1__ bc; int /*<<< orphan*/  seq; } ;
typedef  TYPE_2__ br_sslrec_ccm_context ;
typedef  int /*<<< orphan*/  br_ccm_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_ccm_aad_inject (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  br_ccm_check_tag (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  br_ccm_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ccm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ccm_reset (int /*<<< orphan*/ *,unsigned char*,int,int,size_t,int) ; 
 int /*<<< orphan*/  br_ccm_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_enc16be (unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_enc64be (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,int) ; 

__attribute__((used)) static unsigned char *
ccm_decrypt(br_sslrec_ccm_context *cc,
	int record_type, unsigned version, void *data, size_t *data_len)
{
	br_ccm_context zc;
	unsigned char *buf;
	unsigned char nonce[12], header[13];
	size_t len;

	buf = (unsigned char *)data + 8;
	len = *data_len - (8 + cc->tag_len);

	/*
	 * Make nonce (implicit + explicit parts).
	 */
	memcpy(nonce, cc->iv, sizeof cc->iv);
	memcpy(nonce + 4, data, 8);

	/*
	 * Assemble synthetic header for the AAD.
	 */
	br_enc64be(header, cc->seq ++);
	header[8] = (unsigned char)record_type;
	br_enc16be(header + 9, version);
	br_enc16be(header + 11, len);

	/*
	 * Perform CCM decryption.
	 */
	br_ccm_init(&zc, &cc->bc.vtable);
	br_ccm_reset(&zc, nonce, sizeof nonce, sizeof header, len, cc->tag_len);
	br_ccm_aad_inject(&zc, header, sizeof header);
	br_ccm_flip(&zc);
	br_ccm_run(&zc, 0, buf, len);
	if (!br_ccm_check_tag(&zc, buf + len)) {
		return NULL;
	}
	*data_len = len;
	return buf;
}