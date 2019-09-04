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
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int lzbench_lzma_compress (char*,int,char*,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lzbench_lzma_decompress (char*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

void __attribute__ ((noinline)) doit(char *buffer, int size, int i) {
  static char *buffer2 = NULL;
  static char *buffer3 = NULL;

  unsigned long maxCompressedSize = size * 2 + 10000; // whatever

  if (!buffer2) buffer2 = (char*)malloc(maxCompressedSize);
  if (!buffer3) buffer3 = (char*)malloc(size);

  int64_t compressedSize = lzbench_lzma_compress(buffer, size, buffer2, maxCompressedSize, 4 /*level*/, 0, NULL);

  if (i == 0) printf("sizes: %d,%d\n", size, (int32_t)compressedSize);

  int64_t roundTrip = lzbench_lzma_decompress(buffer2, compressedSize, buffer3, size, 0, 0, NULL);

  assert(roundTrip == size);
  if (i == 0) assert(strcmp(buffer, buffer3) == 0);
}