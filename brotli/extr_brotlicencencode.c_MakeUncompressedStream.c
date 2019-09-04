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
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int const*,unsigned int) ; 

__attribute__((used)) static size_t MakeUncompressedStream(
    const uint8_t* input, size_t input_size, uint8_t* output) {
  size_t size = input_size;
  size_t result = 0;
  size_t offset = 0;
  if (input_size == 0) {
    output[0] = 6;
    return 1;
  }
  output[result++] = 0x21;  /* window bits = 10, is_last = false */
  output[result++] = 0x03;  /* empty metadata, padding */
  while (size > 0) {
    uint32_t nibbles = 0;
    uint32_t chunk_size;
    uint32_t bits;
    chunk_size = (size > (1u << 24)) ? (1u << 24) : (uint32_t)size;
    if (chunk_size > (1u << 16)) nibbles = (chunk_size > (1u << 20)) ? 2 : 1;
    bits =
        (nibbles << 1) | ((chunk_size - 1) << 3) | (1u << (19 + 4 * nibbles));
    output[result++] = (uint8_t)bits;
    output[result++] = (uint8_t)(bits >> 8);
    output[result++] = (uint8_t)(bits >> 16);
    if (nibbles == 2) output[result++] = (uint8_t)(bits >> 24);
    memcpy(&output[result], &input[offset], chunk_size);
    result += chunk_size;
    offset += chunk_size;
    size -= chunk_size;
  }
  output[result++] = 3;
  return result;
}