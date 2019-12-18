#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int distance_postfix_bits; int num_direct_distance_codes; } ;
struct TYPE_6__ {int quality; int lgwin; int lgblock; int size_hint; int stream_offset; TYPE_1__ dist; void* large_window; void* disable_literal_context_modeling; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {TYPE_2__ params; scalar_t__ is_initialized_; } ;
typedef  TYPE_3__ BrotliEncoderState ;
typedef  int BrotliEncoderParameter ;
typedef  int /*<<< orphan*/  BrotliEncoderMode ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FALSE ; 
#define  BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING 137 
#define  BROTLI_PARAM_LARGE_WINDOW 136 
#define  BROTLI_PARAM_LGBLOCK 135 
#define  BROTLI_PARAM_LGWIN 134 
#define  BROTLI_PARAM_MODE 133 
#define  BROTLI_PARAM_NDIRECT 132 
#define  BROTLI_PARAM_NPOSTFIX 131 
#define  BROTLI_PARAM_QUALITY 130 
#define  BROTLI_PARAM_SIZE_HINT 129 
#define  BROTLI_PARAM_STREAM_OFFSET 128 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 void* TO_BROTLI_BOOL (int) ; 

BROTLI_BOOL BrotliEncoderSetParameter(
    BrotliEncoderState* state, BrotliEncoderParameter p, uint32_t value) {
  /* Changing parameters on the fly is not implemented yet. */
  if (state->is_initialized_) return BROTLI_FALSE;
  /* TODO: Validate/clamp parameters here. */
  switch (p) {
    case BROTLI_PARAM_MODE:
      state->params.mode = (BrotliEncoderMode)value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_QUALITY:
      state->params.quality = (int)value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_LGWIN:
      state->params.lgwin = (int)value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_LGBLOCK:
      state->params.lgblock = (int)value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING:
      if ((value != 0) && (value != 1)) return BROTLI_FALSE;
      state->params.disable_literal_context_modeling = TO_BROTLI_BOOL(!!value);
      return BROTLI_TRUE;

    case BROTLI_PARAM_SIZE_HINT:
      state->params.size_hint = value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_LARGE_WINDOW:
      state->params.large_window = TO_BROTLI_BOOL(!!value);
      return BROTLI_TRUE;

    case BROTLI_PARAM_NPOSTFIX:
      state->params.dist.distance_postfix_bits = value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_NDIRECT:
      state->params.dist.num_direct_distance_codes = value;
      return BROTLI_TRUE;

    case BROTLI_PARAM_STREAM_OFFSET:
      if (value > (1u << 30)) return BROTLI_FALSE;
      state->params.stream_offset = value;
      return BROTLI_TRUE;

    default: return BROTLI_FALSE;
  }
}