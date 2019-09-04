#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ substate_tree_group; size_t htree_index; int /*<<< orphan*/  next; } ;
struct TYPE_8__ {TYPE_3__ header; } ;
struct TYPE_11__ {TYPE_1__ arena; } ;
struct TYPE_9__ {size_t num_htrees; int /*<<< orphan*/ * htrees; int /*<<< orphan*/  alphabet_size_limit; int /*<<< orphan*/  alphabet_size_max; int /*<<< orphan*/  codes; } ;
typedef  TYPE_2__ HuffmanTreeGroup ;
typedef  TYPE_3__ BrotliMetablockHeaderArena ;
typedef  TYPE_4__ BrotliDecoderState ;
typedef  scalar_t__ BrotliDecoderErrorCode ;

/* Variables and functions */
 scalar_t__ BROTLI_DECODER_SUCCESS ; 
 scalar_t__ BROTLI_STATE_TREE_GROUP_LOOP ; 
 scalar_t__ BROTLI_STATE_TREE_GROUP_NONE ; 
 scalar_t__ ReadHuffmanCode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,TYPE_4__*) ; 

__attribute__((used)) static BrotliDecoderErrorCode HuffmanTreeGroupDecode(
    HuffmanTreeGroup* group, BrotliDecoderState* s) {
  BrotliMetablockHeaderArena* h = &s->arena.header;
  if (h->substate_tree_group != BROTLI_STATE_TREE_GROUP_LOOP) {
    h->next = group->codes;
    h->htree_index = 0;
    h->substate_tree_group = BROTLI_STATE_TREE_GROUP_LOOP;
  }
  while (h->htree_index < group->num_htrees) {
    uint32_t table_size;
    BrotliDecoderErrorCode result = ReadHuffmanCode(group->alphabet_size_max,
        group->alphabet_size_limit, h->next, &table_size, s);
    if (result != BROTLI_DECODER_SUCCESS) return result;
    group->htrees[h->htree_index] = h->next;
    h->next += table_size;
    ++h->htree_index;
  }
  h->substate_tree_group = BROTLI_STATE_TREE_GROUP_NONE;
  return BROTLI_DECODER_SUCCESS;
}