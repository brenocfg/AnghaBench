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
typedef  int /*<<< orphan*/  brotli_free_func ;
typedef  scalar_t__ brotli_alloc_func ;
struct TYPE_8__ {int /*<<< orphan*/ * htrees; int /*<<< orphan*/ * codes; } ;
struct TYPE_7__ {int /*<<< orphan*/ * htrees; int /*<<< orphan*/ * codes; } ;
struct TYPE_6__ {int /*<<< orphan*/ * htrees; int /*<<< orphan*/ * codes; } ;
struct TYPE_9__ {int canny_ringbuffer_allocation; int* dist_rb; int mtf_upper_bound; int /*<<< orphan*/  transforms; int /*<<< orphan*/  dictionary; int /*<<< orphan*/ * block_len_trees; int /*<<< orphan*/ * block_type_trees; scalar_t__ dist_rb_idx; scalar_t__ max_distance; scalar_t__ window_bits; scalar_t__ should_wrap_ringbuffer; scalar_t__ is_metadata; scalar_t__ is_uncompressed; scalar_t__ is_last_metablock; TYPE_3__ distance_hgroup; TYPE_2__ insert_copy_hgroup; TYPE_1__ literal_hgroup; int /*<<< orphan*/ * dist_context_map_slice; int /*<<< orphan*/ * context_map_slice; int /*<<< orphan*/ * dist_context_map; int /*<<< orphan*/ * context_modes; int /*<<< orphan*/ * context_map; scalar_t__ ringbuffer_mask; scalar_t__ new_ringbuffer_size; scalar_t__ ringbuffer_size; int /*<<< orphan*/ * ringbuffer; scalar_t__ partial_pos_out; scalar_t__ rb_roundtrips; scalar_t__ pos; scalar_t__ loop_counter; scalar_t__ buffer_length; int /*<<< orphan*/  substate_read_block_length; int /*<<< orphan*/  substate_decode_uint8; int /*<<< orphan*/  substate_uncompressed; int /*<<< orphan*/  substate_metablock_header; scalar_t__ large_window; int /*<<< orphan*/  state; int /*<<< orphan*/  br; scalar_t__ error_code; void* memory_manager_opaque; int /*<<< orphan*/  free_func; scalar_t__ alloc_func; } ;
typedef  TYPE_4__ BrotliDecoderState ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_STATE_DECODE_UINT8_NONE ; 
 int /*<<< orphan*/  BROTLI_STATE_METABLOCK_HEADER_NONE ; 
 int /*<<< orphan*/  BROTLI_STATE_READ_BLOCK_LENGTH_NONE ; 
 int /*<<< orphan*/  BROTLI_STATE_UNCOMPRESSED_NONE ; 
 int /*<<< orphan*/  BROTLI_STATE_UNINITED ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 scalar_t__ BrotliDefaultAllocFunc ; 
 int /*<<< orphan*/  BrotliDefaultFreeFunc ; 
 int /*<<< orphan*/  BrotliGetDictionary () ; 
 int /*<<< orphan*/  BrotliGetTransforms () ; 
 int /*<<< orphan*/  BrotliInitBitReader (int /*<<< orphan*/ *) ; 

BROTLI_BOOL BrotliDecoderStateInit(BrotliDecoderState* s,
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque) {
  if (!alloc_func) {
    s->alloc_func = BrotliDefaultAllocFunc;
    s->free_func = BrotliDefaultFreeFunc;
    s->memory_manager_opaque = 0;
  } else {
    s->alloc_func = alloc_func;
    s->free_func = free_func;
    s->memory_manager_opaque = opaque;
  }

  s->error_code = 0; /* BROTLI_DECODER_NO_ERROR */

  BrotliInitBitReader(&s->br);
  s->state = BROTLI_STATE_UNINITED;
  s->large_window = 0;
  s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
  s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE;
  s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
  s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;

  s->buffer_length = 0;
  s->loop_counter = 0;
  s->pos = 0;
  s->rb_roundtrips = 0;
  s->partial_pos_out = 0;

  s->block_type_trees = NULL;
  s->block_len_trees = NULL;
  s->ringbuffer = NULL;
  s->ringbuffer_size = 0;
  s->new_ringbuffer_size = 0;
  s->ringbuffer_mask = 0;

  s->context_map = NULL;
  s->context_modes = NULL;
  s->dist_context_map = NULL;
  s->context_map_slice = NULL;
  s->dist_context_map_slice = NULL;

  s->literal_hgroup.codes = NULL;
  s->literal_hgroup.htrees = NULL;
  s->insert_copy_hgroup.codes = NULL;
  s->insert_copy_hgroup.htrees = NULL;
  s->distance_hgroup.codes = NULL;
  s->distance_hgroup.htrees = NULL;

  s->is_last_metablock = 0;
  s->is_uncompressed = 0;
  s->is_metadata = 0;
  s->should_wrap_ringbuffer = 0;
  s->canny_ringbuffer_allocation = 1;

  s->window_bits = 0;
  s->max_distance = 0;
  s->dist_rb[0] = 16;
  s->dist_rb[1] = 15;
  s->dist_rb[2] = 11;
  s->dist_rb[3] = 4;
  s->dist_rb_idx = 0;
  s->block_type_trees = NULL;
  s->block_len_trees = NULL;

  s->mtf_upper_bound = 63;

  s->dictionary = BrotliGetDictionary();
  s->transforms = BrotliGetTransforms();

  return BROTLI_TRUE;
}