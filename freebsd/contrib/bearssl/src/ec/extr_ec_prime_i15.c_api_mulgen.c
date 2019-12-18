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

/* Variables and functions */
 unsigned char* api_generator (int,size_t*) ; 
 int /*<<< orphan*/  api_mul (unsigned char*,size_t,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 

__attribute__((used)) static size_t
api_mulgen(unsigned char *R,
	const unsigned char *x, size_t xlen, int curve)
{
	const unsigned char *G;
	size_t Glen;

	G = api_generator(curve, &Glen);
	memcpy(R, G, Glen);
	api_mul(R, Glen, x, xlen, curve);
	return Glen;
}