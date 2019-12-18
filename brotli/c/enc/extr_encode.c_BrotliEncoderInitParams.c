#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  max_distance; int /*<<< orphan*/  alphabet_size_max; int /*<<< orphan*/  alphabet_size_limit; scalar_t__ num_direct_distance_codes; scalar_t__ distance_postfix_bits; } ;
struct TYPE_5__ {TYPE_1__ dist; int /*<<< orphan*/  dictionary; void* disable_literal_context_modeling; scalar_t__ size_hint; scalar_t__ stream_offset; scalar_t__ lgblock; int /*<<< orphan*/  lgwin; int /*<<< orphan*/  quality; void* large_window; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ BrotliEncoderParams ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DEFAULT_MODE ; 
 int /*<<< orphan*/  BROTLI_DEFAULT_QUALITY ; 
 int /*<<< orphan*/  BROTLI_DEFAULT_WINDOW ; 
 int /*<<< orphan*/  BROTLI_DISTANCE_ALPHABET_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_MAX_DISTANCE ; 
 int /*<<< orphan*/  BROTLI_MAX_DISTANCE_BITS ; 
 int /*<<< orphan*/  BrotliInitEncoderDictionary (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void BrotliEncoderInitParams(BrotliEncoderParams* params) {
  params->mode = BROTLI_DEFAULT_MODE;
  params->large_window = BROTLI_FALSE;
  params->quality = BROTLI_DEFAULT_QUALITY;
  params->lgwin = BROTLI_DEFAULT_WINDOW;
  params->lgblock = 0;
  params->stream_offset = 0;
  params->size_hint = 0;
  params->disable_literal_context_modeling = BROTLI_FALSE;
  BrotliInitEncoderDictionary(&params->dictionary);
  params->dist.distance_postfix_bits = 0;
  params->dist.num_direct_distance_codes = 0;
  params->dist.alphabet_size_max =
      BROTLI_DISTANCE_ALPHABET_SIZE(0, 0, BROTLI_MAX_DISTANCE_BITS);
  params->dist.alphabet_size_limit = params->dist.alphabet_size_max;
  params->dist.max_distance = BROTLI_MAX_DISTANCE;
}