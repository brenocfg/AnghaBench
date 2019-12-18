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
struct TYPE_3__ {unsigned char* k; } ;
typedef  TYPE_1__ key_set ;

/* Variables and functions */
 int DECRYPTION_MODE ; 
 scalar_t__* S1 ; 
 scalar_t__* S2 ; 
 scalar_t__* S3 ; 
 scalar_t__* S4 ; 
 scalar_t__* S5 ; 
 scalar_t__* S6 ; 
 scalar_t__* S7 ; 
 scalar_t__* S8 ; 
 int* final_message_permutation ; 
 int* initial_message_permutation ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int* message_expansion ; 
 int* right_sub_message_permutation ; 

void process_message(unsigned char* message_piece, unsigned char* processed_piece, key_set* key_sets, int mode) {
  int           i, k;
  int           shift_size;
  unsigned char shift_byte;

  unsigned char initial_permutation[8];
  memset(initial_permutation, 0, 8);
  memset(processed_piece, 0, 8);

  for (i = 0; i < 64; i++) {
    shift_size = initial_message_permutation[i];
    shift_byte = 0x80 >> ((shift_size - 1) % 8);
    shift_byte &= message_piece[(shift_size - 1) / 8];
    shift_byte <<= ((shift_size - 1) % 8);

    initial_permutation[i / 8] |= (shift_byte >> i % 8);
  }

  unsigned char l[4], r[4];
  for (i = 0; i < 4; i++) {
    l[i] = initial_permutation[i];
    r[i] = initial_permutation[i + 4];
  }

  unsigned char ln[4], rn[4], er[6], ser[4];

  int key_index;
  for (k = 1; k <= 16; k++) {
    memcpy(ln, r, 4);

    memset(er, 0, 6);

    for (i = 0; i < 48; i++) {
      shift_size = message_expansion[i];
      shift_byte = 0x80 >> ((shift_size - 1) % 8);
      shift_byte &= r[(shift_size - 1) / 8];
      shift_byte <<= ((shift_size - 1) % 8);

      er[i / 8] |= (shift_byte >> i % 8);
    }

    if (mode == DECRYPTION_MODE) {
      key_index = 17 - k;
    } else {
      key_index = k;
    }

    for (i = 0; i < 6; i++) {
      er[i] ^= key_sets[key_index].k[i];
    }

    unsigned char row, column;

    for (i = 0; i < 4; i++) {
      ser[i] = 0;
    }

    // 0000 0000 0000 0000 0000 0000
    // rccc crrc cccr rccc crrc cccr

    // Byte 1
    row = 0;
    row |= ((er[0] & 0x80) >> 6);
    row |= ((er[0] & 0x04) >> 2);

    column = 0;
    column |= ((er[0] & 0x78) >> 3);

    ser[0] |= ((unsigned char)S1[row * 16 + column] << 4);

    row = 0;
    row |= (er[0] & 0x02);
    row |= ((er[1] & 0x10) >> 4);

    column = 0;
    column |= ((er[0] & 0x01) << 3);
    column |= ((er[1] & 0xE0) >> 5);

    ser[0] |= (unsigned char)S2[row * 16 + column];

    // Byte 2
    row = 0;
    row |= ((er[1] & 0x08) >> 2);
    row |= ((er[2] & 0x40) >> 6);

    column = 0;
    column |= ((er[1] & 0x07) << 1);
    column |= ((er[2] & 0x80) >> 7);

    ser[1] |= ((unsigned char)S3[row * 16 + column] << 4);

    row = 0;
    row |= ((er[2] & 0x20) >> 4);
    row |= (er[2] & 0x01);

    column = 0;
    column |= ((er[2] & 0x1E) >> 1);

    ser[1] |= (unsigned char)S4[row * 16 + column];

    // Byte 3
    row = 0;
    row |= ((er[3] & 0x80) >> 6);
    row |= ((er[3] & 0x04) >> 2);

    column = 0;
    column |= ((er[3] & 0x78) >> 3);

    ser[2] |= ((unsigned char)S5[row * 16 + column] << 4);

    row = 0;
    row |= (er[3] & 0x02);
    row |= ((er[4] & 0x10) >> 4);

    column = 0;
    column |= ((er[3] & 0x01) << 3);
    column |= ((er[4] & 0xE0) >> 5);

    ser[2] |= (unsigned char)S6[row * 16 + column];

    // Byte 4
    row = 0;
    row |= ((er[4] & 0x08) >> 2);
    row |= ((er[5] & 0x40) >> 6);

    column = 0;
    column |= ((er[4] & 0x07) << 1);
    column |= ((er[5] & 0x80) >> 7);

    ser[3] |= ((unsigned char)S7[row * 16 + column] << 4);

    row = 0;
    row |= ((er[5] & 0x20) >> 4);
    row |= (er[5] & 0x01);

    column = 0;
    column |= ((er[5] & 0x1E) >> 1);

    ser[3] |= (unsigned char)S8[row * 16 + column];

    for (i = 0; i < 4; i++) {
      rn[i] = 0;
    }

    for (i = 0; i < 32; i++) {
      shift_size = right_sub_message_permutation[i];
      shift_byte = 0x80 >> ((shift_size - 1) % 8);
      shift_byte &= ser[(shift_size - 1) / 8];
      shift_byte <<= ((shift_size - 1) % 8);

      rn[i / 8] |= (shift_byte >> i % 8);
    }

    for (i = 0; i < 4; i++) {
      rn[i] ^= l[i];
    }

    for (i = 0; i < 4; i++) {
      l[i] = ln[i];
      r[i] = rn[i];
    }
  }

  unsigned char pre_end_permutation[8];
  for (i = 0; i < 4; i++) {
    pre_end_permutation[i] = r[i];
    pre_end_permutation[4 + i] = l[i];
  }

  for (i = 0; i < 64; i++) {
    shift_size = final_message_permutation[i];
    shift_byte = 0x80 >> ((shift_size - 1) % 8);
    shift_byte &= pre_end_permutation[(shift_size - 1) / 8];
    shift_byte <<= ((shift_size - 1) % 8);

    processed_piece[i / 8] |= (shift_byte >> i % 8);
  }
}