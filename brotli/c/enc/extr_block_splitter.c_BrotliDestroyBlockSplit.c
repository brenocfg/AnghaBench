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
struct TYPE_3__ {int /*<<< orphan*/  lengths; int /*<<< orphan*/  types; } ;
typedef  int /*<<< orphan*/  MemoryManager ;
typedef  TYPE_1__ BlockSplit ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void BrotliDestroyBlockSplit(MemoryManager* m, BlockSplit* self) {
  BROTLI_FREE(m, self->types);
  BROTLI_FREE(m, self->lengths);
}