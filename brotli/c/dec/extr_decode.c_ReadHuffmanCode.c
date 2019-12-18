#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_10__ {int substate_huffman; size_t sub_loop_counter; int space; size_t symbol; size_t* next_symbol; int* symbol_lists; int /*<<< orphan*/ * code_length_histo; int /*<<< orphan*/  repeat_code_len; int /*<<< orphan*/  repeat; int /*<<< orphan*/  prev_code_len; int /*<<< orphan*/ * code_length_code_lengths; int /*<<< orphan*/  table; int /*<<< orphan*/  symbols_lists_array; } ;
struct TYPE_9__ {TYPE_2__ header; } ;
struct TYPE_11__ {TYPE_1__ arena; int /*<<< orphan*/  br; } ;
typedef  int /*<<< orphan*/  HuffmanCode ;
typedef  TYPE_2__ BrotliMetablockHeaderArena ;
typedef  TYPE_3__ BrotliDecoderState ;
typedef  int /*<<< orphan*/  BrotliDecoderErrorCode ;
typedef  int /*<<< orphan*/  BrotliBitReader ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE ; 
 int /*<<< orphan*/  BROTLI_DECODER_ERROR_UNREACHABLE ; 
 int /*<<< orphan*/  BROTLI_DECODER_NEEDS_MORE_INPUT ; 
 int /*<<< orphan*/  BROTLI_DECODER_SUCCESS ; 
 int /*<<< orphan*/  BROTLI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t BROTLI_HUFFMAN_MAX_CODE_LENGTH ; 
 int /*<<< orphan*/  BROTLI_HUFFMAN_MAX_CODE_LENGTH_CODE_LENGTH ; 
 int /*<<< orphan*/  BROTLI_INITIAL_REPEATED_CODE_LENGTH ; 
 int /*<<< orphan*/  BROTLI_LOG (char*) ; 
 int /*<<< orphan*/  BROTLI_LOG_UINT (size_t) ; 
#define  BROTLI_STATE_HUFFMAN_COMPLEX 133 
#define  BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS 132 
#define  BROTLI_STATE_HUFFMAN_NONE 131 
#define  BROTLI_STATE_HUFFMAN_SIMPLE_BUILD 130 
#define  BROTLI_STATE_HUFFMAN_SIMPLE_READ 129 
#define  BROTLI_STATE_HUFFMAN_SIMPLE_SIZE 128 
 int /*<<< orphan*/  BrotliBuildCodeLengthsHuffmanTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t BrotliBuildHuffmanTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 size_t BrotliBuildSimpleHuffmanTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  BrotliSafeReadBits (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  HUFFMAN_TABLE_BITS ; 
 int /*<<< orphan*/  ReadCodeLengthCodeLengths (TYPE_3__*) ; 
 int /*<<< orphan*/  ReadSimpleHuffmanSymbols (size_t,size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  ReadSymbolCodeLengths (size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  SafeReadSymbolCodeLengths (size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BrotliDecoderErrorCode ReadHuffmanCode(uint32_t alphabet_size_max,
                                              uint32_t alphabet_size_limit,
                                              HuffmanCode* table,
                                              uint32_t* opt_table_size,
                                              BrotliDecoderState* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  /* State machine. */
  for (;;) {
    switch (h->substate_huffman) {
      case BROTLI_STATE_HUFFMAN_NONE:
        if (!BrotliSafeReadBits(br, 2, &h->sub_loop_counter)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        BROTLI_LOG_UINT(h->sub_loop_counter);
        /* The value is used as follows:
           1 for simple code;
           0 for no skipping, 2 skips 2 code lengths, 3 skips 3 code lengths */
        if (h->sub_loop_counter != 1) {
          h->space = 32;
          h->repeat = 0;  /* num_codes */
          memset(&h->code_length_histo[0], 0, sizeof(h->code_length_histo[0]) *
              (BROTLI_HUFFMAN_MAX_CODE_LENGTH_CODE_LENGTH + 1));
          memset(&h->code_length_code_lengths[0], 0,
              sizeof(h->code_length_code_lengths));
          h->substate_huffman = BROTLI_STATE_HUFFMAN_COMPLEX;
          continue;
        }
      /* Fall through. */

      case BROTLI_STATE_HUFFMAN_SIMPLE_SIZE:
        /* Read symbols, codes & code lengths directly. */
        if (!BrotliSafeReadBits(br, 2, &h->symbol)) {  /* num_symbols */
          h->substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_SIZE;
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        h->sub_loop_counter = 0;
      /* Fall through. */

      case BROTLI_STATE_HUFFMAN_SIMPLE_READ: {
        BrotliDecoderErrorCode result =
            ReadSimpleHuffmanSymbols(alphabet_size_max, alphabet_size_limit, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }
      }
      /* Fall through. */

      case BROTLI_STATE_HUFFMAN_SIMPLE_BUILD: {
        uint32_t table_size;
        if (h->symbol == 3) {
          uint32_t bits;
          if (!BrotliSafeReadBits(br, 1, &bits)) {
            h->substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_BUILD;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          h->symbol += bits;
        }
        BROTLI_LOG_UINT(h->symbol);
        table_size = BrotliBuildSimpleHuffmanTable(
            table, HUFFMAN_TABLE_BITS, h->symbols_lists_array, h->symbol);
        if (opt_table_size) {
          *opt_table_size = table_size;
        }
        h->substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        return BROTLI_DECODER_SUCCESS;
      }

      /* Decode Huffman-coded code lengths. */
      case BROTLI_STATE_HUFFMAN_COMPLEX: {
        uint32_t i;
        BrotliDecoderErrorCode result = ReadCodeLengthCodeLengths(s);
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }
        BrotliBuildCodeLengthsHuffmanTable(h->table,
                                           h->code_length_code_lengths,
                                           h->code_length_histo);
        memset(&h->code_length_histo[0], 0, sizeof(h->code_length_histo));
        for (i = 0; i <= BROTLI_HUFFMAN_MAX_CODE_LENGTH; ++i) {
          h->next_symbol[i] = (int)i - (BROTLI_HUFFMAN_MAX_CODE_LENGTH + 1);
          h->symbol_lists[h->next_symbol[i]] = 0xFFFF;
        }

        h->symbol = 0;
        h->prev_code_len = BROTLI_INITIAL_REPEATED_CODE_LENGTH;
        h->repeat = 0;
        h->repeat_code_len = 0;
        h->space = 32768;
        h->substate_huffman = BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS;
      }
      /* Fall through. */

      case BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS: {
        uint32_t table_size;
        BrotliDecoderErrorCode result = ReadSymbolCodeLengths(
            alphabet_size_limit, s);
        if (result == BROTLI_DECODER_NEEDS_MORE_INPUT) {
          result = SafeReadSymbolCodeLengths(alphabet_size_limit, s);
        }
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }

        if (h->space != 0) {
          BROTLI_LOG(("[ReadHuffmanCode] space = %d\n", (int)h->space));
          return BROTLI_FAILURE(BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE);
        }
        table_size = BrotliBuildHuffmanTable(
            table, HUFFMAN_TABLE_BITS, h->symbol_lists, h->code_length_histo);
        if (opt_table_size) {
          *opt_table_size = table_size;
        }
        h->substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        return BROTLI_DECODER_SUCCESS;
      }

      default:
        return
            BROTLI_FAILURE(BROTLI_DECODER_ERROR_UNREACHABLE);
    }
  }
}