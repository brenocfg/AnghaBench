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
typedef  unsigned char uint32_t ;
typedef  int /*<<< orphan*/  br_sslrec_gcm_context ;

/* Variables and functions */
 int /*<<< orphan*/  do_ctr (int /*<<< orphan*/ *,void*,unsigned char*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  do_tag (int /*<<< orphan*/ *,int,unsigned int,unsigned char*,size_t,unsigned char*) ; 

__attribute__((used)) static unsigned char *
gcm_decrypt(br_sslrec_gcm_context *cc,
	int record_type, unsigned version, void *data, size_t *data_len)
{
	unsigned char *buf;
	size_t len, u;
	uint32_t bad;
	unsigned char tag[16];

	buf = (unsigned char *)data + 8;
	len = *data_len - 24;
	do_tag(cc, record_type, version, buf, len, tag);
	do_ctr(cc, data, buf, len, tag);

	/*
	 * Compare the computed tag with the value from the record. It
	 * is possibly useless to do a constant-time comparison here,
	 * but it does not hurt.
	 */
	bad = 0;
	for (u = 0; u < 16; u ++) {
		bad |= tag[u] ^ buf[len + u];
	}
	if (bad) {
		return NULL;
	}
	*data_len = len;
	return buf;
}