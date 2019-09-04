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
struct sha256 {int* h; scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static void sha256_init(struct sha256 *s)
{
	s->len = 0;
	s->h[0] = 0x6a09e667;
	s->h[1] = 0xbb67ae85;
	s->h[2] = 0x3c6ef372;
	s->h[3] = 0xa54ff53a;
	s->h[4] = 0x510e527f;
	s->h[5] = 0x9b05688c;
	s->h[6] = 0x1f83d9ab;
	s->h[7] = 0x5be0cd19;
}