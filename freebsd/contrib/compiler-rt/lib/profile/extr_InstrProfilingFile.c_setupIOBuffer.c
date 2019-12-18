#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DynamicBufferIOBuffer ; 
 int /*<<< orphan*/  VPBufferSize ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 char* getenv (char*) ; 

__attribute__((used)) static void setupIOBuffer() {
  const char *BufferSzStr = 0;
  BufferSzStr = getenv("LLVM_VP_BUFFER_SIZE");
  if (BufferSzStr && BufferSzStr[0]) {
    VPBufferSize = atoi(BufferSzStr);
    DynamicBufferIOBuffer = (uint8_t *)calloc(VPBufferSize, 1);
  }
}