#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  literal_buf_; int /*<<< orphan*/  command_buf_; int /*<<< orphan*/  large_table_; int /*<<< orphan*/  hasher_; int /*<<< orphan*/  ringbuffer_; int /*<<< orphan*/  commands_; int /*<<< orphan*/  storage_; int /*<<< orphan*/  memory_manager_; } ;
typedef  int /*<<< orphan*/  MemoryManager ;
typedef  TYPE_1__ BrotliEncoderState ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BROTLI_IS_OOM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliWipeOutMemoryManager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyHasher (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RingBufferFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void BrotliEncoderCleanupState(BrotliEncoderState* s) {
  MemoryManager* m = &s->memory_manager_;
  if (BROTLI_IS_OOM(m)) {
    BrotliWipeOutMemoryManager(m);
    return;
  }
  BROTLI_FREE(m, s->storage_);
  BROTLI_FREE(m, s->commands_);
  RingBufferFree(m, &s->ringbuffer_);
  DestroyHasher(m, &s->hasher_);
  BROTLI_FREE(m, s->large_table_);
  BROTLI_FREE(m, s->command_buf_);
  BROTLI_FREE(m, s->literal_buf_);
}