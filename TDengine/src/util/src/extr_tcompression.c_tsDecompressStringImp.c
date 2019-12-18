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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int LZ4_decompress_safe (char const* const,char* const,int,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char* const,char const* const,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int const) ; 

int tsDecompressStringImp(const char *const input, int compressedSize, char *const output, int outputSize) {
  // compressedSize is the size of data after compression.
  if (input[0] == 1) {
    /* It is compressed by LZ4 algorithm */
    const int decompressed_size = LZ4_decompress_safe(input + 1, output, compressedSize - 1, outputSize);
    if (decompressed_size < 0) {
      char msg[128] = {0};
      sprintf(msg, "decomp_size:%d, Error decompress in LZ4 algorithm!\n", decompressed_size);
      perror(msg);
      exit(EXIT_FAILURE);
    }

    return decompressed_size;
  } else if (input[0] == 0) {
    /* It is not compressed by LZ4 algorithm */
    memcpy(output, input + 1, compressedSize - 1);
    return compressedSize - 1;
  } else {
    perror("Wrong compressed string indicator!\n");
    exit(EXIT_FAILURE);
  }
}