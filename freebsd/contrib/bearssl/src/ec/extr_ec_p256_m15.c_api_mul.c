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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  p256_jacobian ;

/* Variables and functions */
 int /*<<< orphan*/  p256_decode (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  p256_encode (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p256_mul (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  p256_to_affine (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
api_mul(unsigned char *G, size_t Glen,
	const unsigned char *x, size_t xlen, int curve)
{
	uint32_t r;
	p256_jacobian P;

	(void)curve;
	r = p256_decode(&P, G, Glen);
	p256_mul(&P, x, xlen);
	if (Glen >= 65) {
		p256_to_affine(&P);
		p256_encode(G, &P);
	}
	return r;
}