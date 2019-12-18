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
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int set_msg_len (int*,unsigned int,unsigned int) ; 

__attribute__((used)) static int generate_b0(u8 *iv, unsigned int assoclen, unsigned int authsize,
		       unsigned int cryptlen, u8 *b0)
{
	unsigned int l, lp, m = authsize;
	int rc;

	memcpy(b0, iv, 16);

	lp = b0[0];
	l = lp + 1;

	/* set m, bits 3-5 */
	*b0 |= (8 * ((m - 2) / 2));

	/* set adata, bit 6, if associated data is used */
	if (assoclen)
		*b0 |= 64;

	rc = set_msg_len(b0 + 16 - l, cryptlen, l);

	return rc;
}