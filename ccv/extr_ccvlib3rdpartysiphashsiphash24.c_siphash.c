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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIPROUND ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  U64TO8_LE (int /*<<< orphan*/ *,int) ; 
 int U8TO64_LE (int /*<<< orphan*/  const*) ; 
 int cROUNDS ; 
 int dROUNDS ; 

int siphash(uint8_t *out, const uint8_t *in, uint64_t inlen, const uint8_t *k) {
  /* "somepseudorandomlygeneratedbytes" */
  uint64_t v0 = 0x736f6d6570736575ULL;
  uint64_t v1 = 0x646f72616e646f6dULL;
  uint64_t v2 = 0x6c7967656e657261ULL;
  uint64_t v3 = 0x7465646279746573ULL;
  uint64_t b;
  uint64_t k0 = U8TO64_LE(k);
  uint64_t k1 = U8TO64_LE(k + 8);
  uint64_t m;
  int i;
  const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
  const int left = inlen & 7;
  b = ((uint64_t)inlen) << 56;
  v3 ^= k1;
  v2 ^= k0;
  v1 ^= k1;
  v0 ^= k0;

#ifdef DOUBLE
  v1 ^= 0xee;
#endif

  for (; in != end; in += 8) {
    m = U8TO64_LE(in);
    v3 ^= m;

    TRACE;
    for (i = 0; i < cROUNDS; ++i)
      SIPROUND;

    v0 ^= m;
  }

  switch (left) {
  case 7:
    b |= ((uint64_t)in[6]) << 48;
  case 6:
    b |= ((uint64_t)in[5]) << 40;
  case 5:
    b |= ((uint64_t)in[4]) << 32;
  case 4:
    b |= ((uint64_t)in[3]) << 24;
  case 3:
    b |= ((uint64_t)in[2]) << 16;
  case 2:
    b |= ((uint64_t)in[1]) << 8;
  case 1:
    b |= ((uint64_t)in[0]);
    break;
  case 0:
    break;
  }

  v3 ^= b;

  TRACE;
  for (i = 0; i < cROUNDS; ++i)
    SIPROUND;

  v0 ^= b;

#ifndef DOUBLE
  v2 ^= 0xff;
#else
  v2 ^= 0xee;
#endif

  TRACE;
  for (i = 0; i < dROUNDS; ++i)
    SIPROUND;

  b = v0 ^ v1 ^ v2 ^ v3;
  U64TO8_LE(out, b);

#ifdef DOUBLE
  v1 ^= 0xdd;

  TRACE;
  for (i = 0; i < dROUNDS; ++i)
    SIPROUND;

  b = v0 ^ v1 ^ v2 ^ v3;
  U64TO8_LE(out + 8, b);
#endif

  return 0;
}