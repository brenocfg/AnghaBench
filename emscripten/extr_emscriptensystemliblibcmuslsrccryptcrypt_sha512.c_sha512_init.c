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
struct sha512 {int* h; scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static void sha512_init(struct sha512 *s)
{
	s->len = 0;
	s->h[0] = 0x6a09e667f3bcc908ULL;
	s->h[1] = 0xbb67ae8584caa73bULL;
	s->h[2] = 0x3c6ef372fe94f82bULL;
	s->h[3] = 0xa54ff53a5f1d36f1ULL;
	s->h[4] = 0x510e527fade682d1ULL;
	s->h[5] = 0x9b05688c2b3e6c1fULL;
	s->h[6] = 0x1f83d9abfb41bd6bULL;
	s->h[7] = 0x5be0cd19137e2179ULL;
}