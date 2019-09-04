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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compress (unsigned char*,unsigned long*,unsigned char*,int) ; 
 unsigned long compressBound (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  uncompress (unsigned char*,unsigned long*,unsigned char*,int) ; 

void __attribute__ ((noinline)) doit(unsigned char *buffer, int size, int i) {
  static unsigned char *buffer2 = NULL;
  static unsigned char *buffer3 = NULL;

  unsigned long maxCompressedSize = compressBound(size);

  if (!buffer2) buffer2 = (unsigned char*)malloc(maxCompressedSize);
  if (!buffer3) buffer3 = (unsigned char*)malloc(size);

  unsigned long compressedSize = maxCompressedSize;
  compress(buffer2, &compressedSize, buffer, size);
  if (i == 0) printf("sizes: %d,%d\n", size, (int)compressedSize);

  unsigned long decompressedSize = size;
  uncompress(buffer3, &decompressedSize, buffer2, (int)compressedSize);
  assert(decompressedSize == size);
  if (i == 0) assert(strcmp((char*)buffer, (char*)buffer3) == 0);
}