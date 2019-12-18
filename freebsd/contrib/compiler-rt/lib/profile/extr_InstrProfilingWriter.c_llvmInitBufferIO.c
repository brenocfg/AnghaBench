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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ CurOffset; int /*<<< orphan*/  BufferSz; int /*<<< orphan*/ * BufferStart; scalar_t__ OwnFileWriter; int /*<<< orphan*/ * FileWriter; } ;
typedef  int /*<<< orphan*/  ProfDataWriter ;
typedef  TYPE_1__ ProfBufferIO ;

/* Variables and functions */

__attribute__((used)) static void llvmInitBufferIO(ProfBufferIO *BufferIO, ProfDataWriter *FileWriter,
                             uint8_t *Buffer, uint32_t BufferSz) {
  BufferIO->FileWriter = FileWriter;
  BufferIO->OwnFileWriter = 0;
  BufferIO->BufferStart = Buffer;
  BufferIO->BufferSz = BufferSz;
  BufferIO->CurOffset = 0;
}