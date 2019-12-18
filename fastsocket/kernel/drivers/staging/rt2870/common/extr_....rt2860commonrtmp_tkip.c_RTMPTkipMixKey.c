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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
typedef  int UINT ;
typedef  int UCHAR ;
typedef  int INT ;

/* Variables and functions */
 int rotr1 (int) ; 
 int tkip_sbox (int) ; 

VOID RTMPTkipMixKey(
	UCHAR *key,
	UCHAR *ta,
	ULONG pnl, /* Least significant 16 bits of PN */
	ULONG pnh, /* Most significant 32 bits of PN */
	UCHAR *rc4key,
	UINT *p1k)
{

	UINT tsc0;
	UINT tsc1;
	UINT tsc2;

	UINT ppk0;
	UINT ppk1;
	UINT ppk2;
	UINT ppk3;
	UINT ppk4;
	UINT ppk5;

	INT i;
	INT j;

	tsc0 = (unsigned int)((pnh >> 16) % 65536); /* msb */
	tsc1 = (unsigned int)(pnh % 65536);
	tsc2 = (unsigned int)(pnl % 65536); /* lsb */

	/* Phase 1, step 1 */
	p1k[0] = tsc1;
	p1k[1] = tsc0;
	p1k[2] = (UINT)(ta[0] + (ta[1]*256));
	p1k[3] = (UINT)(ta[2] + (ta[3]*256));
	p1k[4] = (UINT)(ta[4] + (ta[5]*256));

	/* Phase 1, step 2 */
	for (i=0; i<8; i++)
	{
		j = 2*(i & 1);
		p1k[0] = (p1k[0] + tkip_sbox( (p1k[4] ^ ((256*key[1+j]) + key[j])) % 65536 )) % 65536;
		p1k[1] = (p1k[1] + tkip_sbox( (p1k[0] ^ ((256*key[5+j]) + key[4+j])) % 65536 )) % 65536;
		p1k[2] = (p1k[2] + tkip_sbox( (p1k[1] ^ ((256*key[9+j]) + key[8+j])) % 65536 )) % 65536;
		p1k[3] = (p1k[3] + tkip_sbox( (p1k[2] ^ ((256*key[13+j]) + key[12+j])) % 65536 )) % 65536;
		p1k[4] = (p1k[4] + tkip_sbox( (p1k[3] ^ (((256*key[1+j]) + key[j]))) % 65536 )) % 65536;
		p1k[4] = (p1k[4] + i) % 65536;
	}

	/* Phase 2, Step 1 */
	ppk0 = p1k[0];
	ppk1 = p1k[1];
	ppk2 = p1k[2];
	ppk3 = p1k[3];
	ppk4 = p1k[4];
	ppk5 = (p1k[4] + tsc2) % 65536;

	/* Phase2, Step 2 */
	ppk0 = ppk0 + tkip_sbox( (ppk5 ^ ((256*key[1]) + key[0])) % 65536);
	ppk1 = ppk1 + tkip_sbox( (ppk0 ^ ((256*key[3]) + key[2])) % 65536);
	ppk2 = ppk2 + tkip_sbox( (ppk1 ^ ((256*key[5]) + key[4])) % 65536);
	ppk3 = ppk3 + tkip_sbox( (ppk2 ^ ((256*key[7]) + key[6])) % 65536);
	ppk4 = ppk4 + tkip_sbox( (ppk3 ^ ((256*key[9]) + key[8])) % 65536);
	ppk5 = ppk5 + tkip_sbox( (ppk4 ^ ((256*key[11]) + key[10])) % 65536);

	ppk0 = ppk0 + rotr1(ppk5 ^ ((256*key[13]) + key[12]));
	ppk1 = ppk1 + rotr1(ppk0 ^ ((256*key[15]) + key[14]));
	ppk2 = ppk2 + rotr1(ppk1);
	ppk3 = ppk3 + rotr1(ppk2);
	ppk4 = ppk4 + rotr1(ppk3);
	ppk5 = ppk5 + rotr1(ppk4);

	/* Phase 2, Step 3 */
    /* Phase 2, Step 3 */

	tsc0 = (unsigned int)((pnh >> 16) % 65536); /* msb */
	tsc1 = (unsigned int)(pnh % 65536);
	tsc2 = (unsigned int)(pnl % 65536); /* lsb */

	rc4key[0] = (tsc2 >> 8) % 256;
	rc4key[1] = (((tsc2 >> 8) % 256) | 0x20) & 0x7f;
	rc4key[2] = tsc2 % 256;
	rc4key[3] = ((ppk5 ^ ((256*key[1]) + key[0])) >> 1) % 256;

	rc4key[4] = ppk0 % 256;
	rc4key[5] = (ppk0 >> 8) % 256;

	rc4key[6] = ppk1 % 256;
	rc4key[7] = (ppk1 >> 8) % 256;

	rc4key[8] = ppk2 % 256;
	rc4key[9] = (ppk2 >> 8) % 256;

	rc4key[10] = ppk3 % 256;
	rc4key[11] = (ppk3 >> 8) % 256;

	rc4key[12] = ppk4 % 256;
	rc4key[13] = (ppk4 >> 8) % 256;

	rc4key[14] = ppk5 % 256;
	rc4key[15] = (ppk5 >> 8) % 256;
}