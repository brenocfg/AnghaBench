#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int distance_postfix_bits; int num_direct_distance_codes; } ;
struct TYPE_6__ {scalar_t__ quality; scalar_t__ mode; TYPE_1__ dist; } ;
typedef  TYPE_2__ BrotliEncoderParams ;

/* Variables and functions */
 int BROTLI_MAX_NDIRECT ; 
 int BROTLI_MAX_NPOSTFIX ; 
 scalar_t__ BROTLI_MODE_FONT ; 
 int /*<<< orphan*/  BrotliInitDistanceParams (TYPE_2__*,int,int) ; 
 scalar_t__ MIN_QUALITY_FOR_NONZERO_DISTANCE_PARAMS ; 

__attribute__((used)) static void ChooseDistanceParams(BrotliEncoderParams* params) {
  uint32_t distance_postfix_bits = 0;
  uint32_t num_direct_distance_codes = 0;

  if (params->quality >= MIN_QUALITY_FOR_NONZERO_DISTANCE_PARAMS) {
    uint32_t ndirect_msb;
    if (params->mode == BROTLI_MODE_FONT) {
      distance_postfix_bits = 1;
      num_direct_distance_codes = 12;
    } else {
      distance_postfix_bits = params->dist.distance_postfix_bits;
      num_direct_distance_codes = params->dist.num_direct_distance_codes;
    }
    ndirect_msb = (num_direct_distance_codes >> distance_postfix_bits) & 0x0F;
    if (distance_postfix_bits > BROTLI_MAX_NPOSTFIX ||
        num_direct_distance_codes > BROTLI_MAX_NDIRECT ||
        (ndirect_msb << distance_postfix_bits) != num_direct_distance_codes) {
      distance_postfix_bits = 0;
      num_direct_distance_codes = 0;
    }
  }

  BrotliInitDistanceParams(
      params, distance_postfix_bits, num_direct_distance_codes);
}