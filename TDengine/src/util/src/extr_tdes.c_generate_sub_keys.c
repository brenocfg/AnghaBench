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
struct TYPE_3__ {unsigned char* k; int* c; int* d; } ;
typedef  TYPE_1__ key_set ;

/* Variables and functions */
 int* initial_key_permutaion ; 
 int* key_shift_sizes ; 
 int* sub_key_permutation ; 

void generate_sub_keys(unsigned char* main_key, key_set* key_sets) {
  int           i, j;
  int           shift_size;
  unsigned char shift_byte, first_shift_bits, second_shift_bits, third_shift_bits, fourth_shift_bits;

  for (i = 0; i < 8; i++) {
    key_sets[0].k[i] = 0;
  }

  for (i = 0; i < 56; i++) {
    shift_size = initial_key_permutaion[i];
    shift_byte = 0x80 >> ((shift_size - 1) % 8);
    shift_byte &= main_key[(shift_size - 1) / 8];
    shift_byte <<= ((shift_size - 1) % 8);

    key_sets[0].k[i / 8] |= (shift_byte >> i % 8);
  }

  for (i = 0; i < 3; i++) {
    key_sets[0].c[i] = key_sets[0].k[i];
  }

  key_sets[0].c[3] = key_sets[0].k[3] & 0xF0;

  for (i = 0; i < 3; i++) {
    key_sets[0].d[i] = (key_sets[0].k[i + 3] & 0x0F) << 4;
    key_sets[0].d[i] |= (key_sets[0].k[i + 4] & 0xF0) >> 4;
  }

  key_sets[0].d[3] = (key_sets[0].k[6] & 0x0F) << 4;

  for (i = 1; i < 17; i++) {
    for (j = 0; j < 4; j++) {
      key_sets[i].c[j] = key_sets[i - 1].c[j];
      key_sets[i].d[j] = key_sets[i - 1].d[j];
    }

    shift_size = key_shift_sizes[i];
    if (shift_size == 1) {
      shift_byte = 0x80;
    } else {
      shift_byte = 0xC0;
    }

    // Process C
    first_shift_bits = shift_byte & key_sets[i].c[0];
    second_shift_bits = shift_byte & key_sets[i].c[1];
    third_shift_bits = shift_byte & key_sets[i].c[2];
    fourth_shift_bits = shift_byte & key_sets[i].c[3];

    key_sets[i].c[0] <<= shift_size;
    key_sets[i].c[0] |= (second_shift_bits >> (8 - shift_size));

    key_sets[i].c[1] <<= shift_size;
    key_sets[i].c[1] |= (third_shift_bits >> (8 - shift_size));

    key_sets[i].c[2] <<= shift_size;
    key_sets[i].c[2] |= (fourth_shift_bits >> (8 - shift_size));

    key_sets[i].c[3] <<= shift_size;
    key_sets[i].c[3] |= (first_shift_bits >> (4 - shift_size));

    // Process D
    first_shift_bits = shift_byte & key_sets[i].d[0];
    second_shift_bits = shift_byte & key_sets[i].d[1];
    third_shift_bits = shift_byte & key_sets[i].d[2];
    fourth_shift_bits = shift_byte & key_sets[i].d[3];

    key_sets[i].d[0] <<= shift_size;
    key_sets[i].d[0] |= (second_shift_bits >> (8 - shift_size));

    key_sets[i].d[1] <<= shift_size;
    key_sets[i].d[1] |= (third_shift_bits >> (8 - shift_size));

    key_sets[i].d[2] <<= shift_size;
    key_sets[i].d[2] |= (fourth_shift_bits >> (8 - shift_size));

    key_sets[i].d[3] <<= shift_size;
    key_sets[i].d[3] |= (first_shift_bits >> (4 - shift_size));

    for (j = 0; j < 48; j++) {
      shift_size = sub_key_permutation[j];
      if (shift_size <= 28) {
        shift_byte = 0x80 >> ((shift_size - 1) % 8);
        shift_byte &= key_sets[i].c[(shift_size - 1) / 8];
        shift_byte <<= ((shift_size - 1) % 8);
      } else {
        shift_byte = 0x80 >> ((shift_size - 29) % 8);
        shift_byte &= key_sets[i].d[(shift_size - 29) / 8];
        shift_byte <<= ((shift_size - 29) % 8);
      }

      key_sets[i].k[j / 8] |= (shift_byte >> j % 8);
    }
  }
}