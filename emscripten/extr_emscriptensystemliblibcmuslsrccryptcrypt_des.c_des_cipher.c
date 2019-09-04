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
typedef  int uint32_t ;
struct expanded_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __do_des (int,int,int*,int*,int,int,struct expanded_key const*) ; 

__attribute__((used)) static void des_cipher(const unsigned char *in, unsigned char *out,
    uint32_t count, uint32_t saltbits, const struct expanded_key *ekey)
{
	uint32_t l_out, r_out, rawl, rawr;

	rawl =
	    (uint32_t)in[3] |
	    ((uint32_t)in[2] << 8) |
	    ((uint32_t)in[1] << 16) |
	    ((uint32_t)in[0] << 24);
	rawr =
	    (uint32_t)in[7] |
	    ((uint32_t)in[6] << 8) |
	    ((uint32_t)in[5] << 16) |
	    ((uint32_t)in[4] << 24);

	__do_des(rawl, rawr, &l_out, &r_out, count, saltbits, ekey);

	out[0] = l_out >> 24;
	out[1] = l_out >> 16;
	out[2] = l_out >> 8;
	out[3] = l_out;
	out[4] = r_out >> 24;
	out[5] = r_out >> 16;
	out[6] = r_out >> 8;
	out[7] = r_out;
}