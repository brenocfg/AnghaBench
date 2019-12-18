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
typedef  int /*<<< orphan*/  jacobian ;
typedef  int /*<<< orphan*/  curve_params ;

/* Variables and functions */
 int /*<<< orphan*/ * id_to_curve (int) ; 
 int /*<<< orphan*/  point_decode (int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  point_encode (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  point_mul (int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static uint32_t
api_mul(unsigned char *G, size_t Glen,
	const unsigned char *x, size_t xlen, int curve)
{
	uint32_t r;
	const curve_params *cc;
	jacobian P;

	cc = id_to_curve(curve);
	r = point_decode(&P, G, Glen, cc);
	point_mul(&P, x, xlen, cc);
	point_encode(G, &P, cc);
	return r;
}