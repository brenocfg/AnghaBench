#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  unsigned int uint32_t ;
struct TYPE_7__ {unsigned int alphabet_size_limit; } ;
struct TYPE_8__ {unsigned int* dist_offset; scalar_t__* dist_extra_bits; } ;
struct TYPE_6__ {TYPE_3__ body; } ;
struct TYPE_9__ {unsigned int distance_postfix_bits; unsigned int num_direct_distance_codes; TYPE_2__ distance_hgroup; TYPE_1__ arena; } ;
typedef  TYPE_3__ BrotliMetablockBodyArena ;
typedef  TYPE_4__ BrotliDecoderState ;

/* Variables and functions */
 unsigned int BROTLI_NUM_DISTANCE_SHORT_CODES ; 

__attribute__((used)) static void CalculateDistanceLut(BrotliDecoderState* s) {
  BrotliMetablockBodyArena* b = &s->arena.body;
  uint32_t npostfix = s->distance_postfix_bits;
  uint32_t ndirect = s->num_direct_distance_codes;
  uint32_t alphabet_size_limit = s->distance_hgroup.alphabet_size_limit;
  uint32_t postfix = 1u << npostfix;
  uint32_t j;
  uint32_t bits = 1;
  uint32_t half = 0;

  /* Skip short codes. */
  uint32_t i = BROTLI_NUM_DISTANCE_SHORT_CODES;

  /* Fill direct codes. */
  for (j = 0; j < ndirect; ++j) {
    b->dist_extra_bits[i] = 0;
    b->dist_offset[i] = j + 1;
    ++i;
  }

  /* Fill regular distance codes. */
  while (i < alphabet_size_limit) {
    uint32_t base = ndirect + ((((2 + half) << bits) - 4) << npostfix) + 1;
    /* Always fill the complete group. */
    for (j = 0; j < postfix; ++j) {
      b->dist_extra_bits[i] = (uint8_t)bits;
      b->dist_offset[i] = base + j;
      ++i;
    }
    bits = bits + half;
    half = half ^ 1;
  }
}