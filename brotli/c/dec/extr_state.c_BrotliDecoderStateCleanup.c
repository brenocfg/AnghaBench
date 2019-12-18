#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  block_type_trees; int /*<<< orphan*/  ringbuffer; } ;
typedef  TYPE_1__ BrotliDecoderState ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DECODER_FREE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BrotliDecoderStateCleanupAfterMetablock (TYPE_1__*) ; 

void BrotliDecoderStateCleanup(BrotliDecoderState* s) {
  BrotliDecoderStateCleanupAfterMetablock(s);

  BROTLI_DECODER_FREE(s, s->ringbuffer);
  BROTLI_DECODER_FREE(s, s->block_type_trees);
}