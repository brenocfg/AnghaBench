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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  table ;
typedef  int brotli_reg_t ;
typedef  int /*<<< orphan*/  HuffmanCode ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DCHECK (int) ; 
 int BROTLI_HUFFMAN_MAX_CODE_LENGTH ; 
 int BROTLI_REVERSE_BITS_LOWEST ; 
 int BROTLI_REVERSE_BITS_MAX ; 
 size_t BrotliReverseBits (int) ; 
 int /*<<< orphan*/  ConstructHuffmanCode (int /*<<< orphan*/ ,int) ; 
 int NextTableBitSize (int*,int,int) ; 
 int /*<<< orphan*/  ReplicateValue (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

uint32_t BrotliBuildHuffmanTable(HuffmanCode* root_table,
                                 int root_bits,
                                 const uint16_t* const symbol_lists,
                                 uint16_t* count) {
  HuffmanCode code;       /* current table entry */
  HuffmanCode* table;     /* next available space in table */
  int len;                /* current code length */
  int symbol;             /* symbol index in original or sorted table */
  brotli_reg_t key;       /* prefix code */
  brotli_reg_t key_step;  /* prefix code addend */
  brotli_reg_t sub_key;   /* 2nd level table prefix code */
  brotli_reg_t sub_key_step;  /* 2nd level table prefix code addend */
  int step;               /* step size to replicate values in current table */
  int table_bits;         /* key length of current table */
  int table_size;         /* size of current table */
  int total_size;         /* sum of root table size and 2nd level table sizes */
  int max_length = -1;
  int bits;
  int bits_count;

  BROTLI_DCHECK(root_bits <= BROTLI_REVERSE_BITS_MAX);
  BROTLI_DCHECK(BROTLI_HUFFMAN_MAX_CODE_LENGTH - root_bits <=
                BROTLI_REVERSE_BITS_MAX);

  while (symbol_lists[max_length] == 0xFFFF) max_length--;
  max_length += BROTLI_HUFFMAN_MAX_CODE_LENGTH + 1;

  table = root_table;
  table_bits = root_bits;
  table_size = 1 << table_bits;
  total_size = table_size;

  /* Fill in the root table. Reduce the table size to if possible,
     and create the repetitions by memcpy. */
  if (table_bits > max_length) {
    table_bits = max_length;
    table_size = 1 << table_bits;
  }
  key = 0;
  key_step = BROTLI_REVERSE_BITS_LOWEST;
  bits = 1;
  step = 2;
  do {
    symbol = bits - (BROTLI_HUFFMAN_MAX_CODE_LENGTH + 1);
    for (bits_count = count[bits]; bits_count != 0; --bits_count) {
      symbol = symbol_lists[symbol];
      code = ConstructHuffmanCode((uint8_t)bits, (uint16_t)symbol);
      ReplicateValue(&table[BrotliReverseBits(key)], step, table_size, code);
      key += key_step;
    }
    step <<= 1;
    key_step >>= 1;
  } while (++bits <= table_bits);

  /* If root_bits != table_bits then replicate to fill the remaining slots. */
  while (total_size != table_size) {
    memcpy(&table[table_size], &table[0],
           (size_t)table_size * sizeof(table[0]));
    table_size <<= 1;
  }

  /* Fill in 2nd level tables and add pointers to root table. */
  key_step = BROTLI_REVERSE_BITS_LOWEST >> (root_bits - 1);
  sub_key = (BROTLI_REVERSE_BITS_LOWEST << 1);
  sub_key_step = BROTLI_REVERSE_BITS_LOWEST;
  for (len = root_bits + 1, step = 2; len <= max_length; ++len) {
    symbol = len - (BROTLI_HUFFMAN_MAX_CODE_LENGTH + 1);
    for (; count[len] != 0; --count[len]) {
      if (sub_key == (BROTLI_REVERSE_BITS_LOWEST << 1U)) {
        table += table_size;
        table_bits = NextTableBitSize(count, len, root_bits);
        table_size = 1 << table_bits;
        total_size += table_size;
        sub_key = BrotliReverseBits(key);
        key += key_step;
        root_table[sub_key] = ConstructHuffmanCode(
            (uint8_t)(table_bits + root_bits),
            (uint16_t)(((size_t)(table - root_table)) - sub_key));
        sub_key = 0;
      }
      symbol = symbol_lists[symbol];
      code = ConstructHuffmanCode((uint8_t)(len - root_bits), (uint16_t)symbol);
      ReplicateValue(
          &table[BrotliReverseBits(sub_key)], step, table_size, code);
      sub_key += sub_key_step;
    }
    step <<= 1;
    sub_key_step >>= 1;
  }
  return (uint32_t)total_size;
}