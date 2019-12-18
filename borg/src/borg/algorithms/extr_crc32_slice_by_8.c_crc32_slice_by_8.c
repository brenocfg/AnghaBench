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
typedef  int uint32_t ;

/* Variables and functions */
 int** Crc32Lookup ; 
 int _le32toh (int) ; 

uint32_t crc32_slice_by_8(const void* data, size_t length, uint32_t previousCrc32)
{
  uint32_t crc = ~previousCrc32; // same as previousCrc32 ^ 0xFFFFFFFF

  const uint32_t* current;
  const uint8_t* currentChar = (const uint8_t*) data;

  // enabling optimization (at least -O2) automatically unrolls the inner for-loop
  const size_t Unroll = 4;
  const size_t BytesAtOnce = 8 * Unroll;

  // wanted: 32 bit / 4 Byte alignment, compute leading, unaligned bytes length
  uintptr_t unaligned_length = (4 - (((uintptr_t) currentChar) & 3)) & 3;
  // process unaligned bytes, if any (standard algorithm)
  while ((length != 0) && (unaligned_length != 0))
  {
    crc = (crc >> 8) ^ Crc32Lookup[0][(crc & 0xFF) ^ *currentChar++];
    length--;
    unaligned_length--;
  }

  // pointer points to 32bit aligned address now
  current = (const uint32_t*) currentChar;

  // process 4x eight bytes at once (Slicing-by-8)
  while (length >= BytesAtOnce)
  {
    size_t unrolling;
    for (unrolling = 0; unrolling < Unroll; unrolling++)
    {
#if BORG_BIG_ENDIAN
      uint32_t one = *current++ ^ _le32toh(crc);
      uint32_t two = *current++;
      crc = Crc32Lookup[0][ two      & 0xFF] ^
            Crc32Lookup[1][(two>> 8) & 0xFF] ^
            Crc32Lookup[2][(two>>16) & 0xFF] ^
            Crc32Lookup[3][(two>>24) & 0xFF] ^
            Crc32Lookup[4][ one      & 0xFF] ^
            Crc32Lookup[5][(one>> 8) & 0xFF] ^
            Crc32Lookup[6][(one>>16) & 0xFF] ^
            Crc32Lookup[7][(one>>24) & 0xFF];
#else
      uint32_t one = *current++ ^ crc;
      uint32_t two = *current++;
      crc = Crc32Lookup[0][(two>>24) & 0xFF] ^
            Crc32Lookup[1][(two>>16) & 0xFF] ^
            Crc32Lookup[2][(two>> 8) & 0xFF] ^
            Crc32Lookup[3][ two      & 0xFF] ^
            Crc32Lookup[4][(one>>24) & 0xFF] ^
            Crc32Lookup[5][(one>>16) & 0xFF] ^
            Crc32Lookup[6][(one>> 8) & 0xFF] ^
            Crc32Lookup[7][ one      & 0xFF];
#endif

    }

    length -= BytesAtOnce;
  }

  currentChar = (const uint8_t*) current;
  // remaining 1 to 31 bytes (standard algorithm)
  while (length-- != 0)
    crc = (crc >> 8) ^ Crc32Lookup[0][(crc & 0xFF) ^ *currentChar++];

  return ~crc; // same as crc ^ 0xFFFFFFFF
}