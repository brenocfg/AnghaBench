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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_ARRAY (int*,int const*) ; 

__attribute__((used)) static void InitCommandPrefixCodes(uint8_t cmd_depths[128],
                                   uint16_t cmd_bits[128],
                                   uint8_t cmd_code[512],
                                   size_t* cmd_code_numbits) {
  static const uint8_t kDefaultCommandDepths[128] = {
    0, 4, 4, 5, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8,
    0, 0, 0, 4, 4, 4, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7,
    7, 7, 10, 10, 10, 10, 10, 10, 0, 4, 4, 5, 5, 5, 6, 6,
    7, 8, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4,
    4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 7, 7, 7, 8, 10,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  };
  static const uint16_t kDefaultCommandBits[128] = {
    0,   0,   8,   9,   3,  35,   7,   71,
    39, 103,  23,  47, 175, 111, 239,   31,
    0,   0,   0,   4,  12,   2,  10,    6,
    13,  29,  11,  43,  27,  59,  87,   55,
    15,  79, 319, 831, 191, 703, 447,  959,
    0,  14,   1,  25,   5,  21,  19,   51,
    119, 159,  95, 223, 479, 991,  63,  575,
    127, 639, 383, 895, 255, 767, 511, 1023,
    14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    27, 59, 7, 39, 23, 55, 30, 1, 17, 9, 25, 5, 0, 8, 4, 12,
    2, 10, 6, 21, 13, 29, 3, 19, 11, 15, 47, 31, 95, 63, 127, 255,
    767, 2815, 1791, 3839, 511, 2559, 1535, 3583, 1023, 3071, 2047, 4095,
  };
  static const uint8_t kDefaultCommandCode[] = {
    0xff, 0x77, 0xd5, 0xbf, 0xe7, 0xde, 0xea, 0x9e, 0x51, 0x5d, 0xde, 0xc6,
    0x70, 0x57, 0xbc, 0x58, 0x58, 0x58, 0xd8, 0xd8, 0x58, 0xd5, 0xcb, 0x8c,
    0xea, 0xe0, 0xc3, 0x87, 0x1f, 0x83, 0xc1, 0x60, 0x1c, 0x67, 0xb2, 0xaa,
    0x06, 0x83, 0xc1, 0x60, 0x30, 0x18, 0xcc, 0xa1, 0xce, 0x88, 0x54, 0x94,
    0x46, 0xe1, 0xb0, 0xd0, 0x4e, 0xb2, 0xf7, 0x04, 0x00,
  };
  static const size_t kDefaultCommandCodeNumBits = 448;
  COPY_ARRAY(cmd_depths, kDefaultCommandDepths);
  COPY_ARRAY(cmd_bits, kDefaultCommandBits);

  /* Initialize the pre-compressed form of the command and distance prefix
     codes. */
  COPY_ARRAY(cmd_code, kDefaultCommandCode);
  *cmd_code_numbits = kDefaultCommandCodeNumBits;
}