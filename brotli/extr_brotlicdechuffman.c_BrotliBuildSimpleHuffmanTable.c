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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  table ;
typedef  int /*<<< orphan*/  HuffmanCode ;

/* Variables and functions */
 int /*<<< orphan*/  ConstructHuffmanCode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

uint32_t BrotliBuildSimpleHuffmanTable(HuffmanCode* table,
                                       int root_bits,
                                       uint16_t* val,
                                       uint32_t num_symbols) {
  uint32_t table_size = 1;
  const uint32_t goal_size = 1U << root_bits;
  switch (num_symbols) {
    case 0:
      table[0] = ConstructHuffmanCode(0, val[0]);
      break;
    case 1:
      if (val[1] > val[0]) {
        table[0] = ConstructHuffmanCode(1, val[0]);
        table[1] = ConstructHuffmanCode(1, val[1]);
      } else {
        table[0] = ConstructHuffmanCode(1, val[1]);
        table[1] = ConstructHuffmanCode(1, val[0]);
      }
      table_size = 2;
      break;
    case 2:
      table[0] = ConstructHuffmanCode(1, val[0]);
      table[2] = ConstructHuffmanCode(1, val[0]);
      if (val[2] > val[1]) {
        table[1] = ConstructHuffmanCode(2, val[1]);
        table[3] = ConstructHuffmanCode(2, val[2]);
      } else {
        table[1] = ConstructHuffmanCode(2, val[2]);
        table[3] = ConstructHuffmanCode(2, val[1]);
      }
      table_size = 4;
      break;
    case 3: {
      int i, k;
      for (i = 0; i < 3; ++i) {
        for (k = i + 1; k < 4; ++k) {
          if (val[k] < val[i]) {
            uint16_t t = val[k];
            val[k] = val[i];
            val[i] = t;
          }
        }
      }
      table[0] = ConstructHuffmanCode(2, val[0]);
      table[2] = ConstructHuffmanCode(2, val[1]);
      table[1] = ConstructHuffmanCode(2, val[2]);
      table[3] = ConstructHuffmanCode(2, val[3]);
      table_size = 4;
      break;
    }
    case 4: {
      if (val[3] < val[2]) {
        uint16_t t = val[3];
        val[3] = val[2];
        val[2] = t;
      }
      table[0] = ConstructHuffmanCode(1, val[0]);
      table[1] = ConstructHuffmanCode(2, val[1]);
      table[2] = ConstructHuffmanCode(1, val[0]);
      table[3] = ConstructHuffmanCode(3, val[2]);
      table[4] = ConstructHuffmanCode(1, val[0]);
      table[5] = ConstructHuffmanCode(2, val[1]);
      table[6] = ConstructHuffmanCode(1, val[0]);
      table[7] = ConstructHuffmanCode(3, val[3]);
      table_size = 8;
      break;
    }
  }
  while (table_size != goal_size) {
    memcpy(&table[table_size], &table[0],
           (size_t)table_size * sizeof(table[0]));
    table_size <<= 1;
  }
  return goal_size;
}