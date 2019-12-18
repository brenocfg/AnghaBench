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
typedef  int /*<<< orphan*/  br_sslrec_chapol_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc16be (unsigned char*,size_t) ; 
 int /*<<< orphan*/  gen_chapol_process (int /*<<< orphan*/ *,int,unsigned int,unsigned char*,size_t,unsigned char*,int) ; 

__attribute__((used)) static unsigned char *
chapol_encrypt(br_sslrec_chapol_context *cc,
	int record_type, unsigned version, void *data, size_t *data_len)
{
	unsigned char *buf;
	size_t len;

	buf = data;
	len = *data_len;
	gen_chapol_process(cc, record_type, version, buf, len, buf + len, 1);
	buf -= 5;
	buf[0] = (unsigned char)record_type;
	br_enc16be(buf + 1, version);
	br_enc16be(buf + 3, len + 16);
	*data_len = len + 21;
	return buf;
}