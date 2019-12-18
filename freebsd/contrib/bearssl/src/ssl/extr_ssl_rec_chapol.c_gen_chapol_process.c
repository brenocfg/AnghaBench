#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  ichacha; int /*<<< orphan*/  key; int /*<<< orphan*/  (* ipoly ) (int /*<<< orphan*/ ,unsigned char*,void*,size_t,unsigned char*,int,void*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  iv; int /*<<< orphan*/  seq; } ;
typedef  TYPE_1__ br_sslrec_chapol_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_enc16be (unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_enc64be (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,void*,size_t,unsigned char*,int,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gen_chapol_process(br_sslrec_chapol_context *cc,
	int record_type, unsigned version, void *data, size_t len,
	void *tag, int encrypt)
{
	unsigned char header[13];
	unsigned char nonce[12];
	uint64_t seq;
	size_t u;

	seq = cc->seq ++;
	br_enc64be(header, seq);
	header[8] = (unsigned char)record_type;
	br_enc16be(header + 9, version);
	br_enc16be(header + 11, len);
	memcpy(nonce, cc->iv, 12);
	for (u = 0; u < 8; u ++) {
		nonce[11 - u] ^= (unsigned char)seq;
		seq >>= 8;
	}
	cc->ipoly(cc->key, nonce, data, len, header, sizeof header,
		tag, cc->ichacha, encrypt);
}