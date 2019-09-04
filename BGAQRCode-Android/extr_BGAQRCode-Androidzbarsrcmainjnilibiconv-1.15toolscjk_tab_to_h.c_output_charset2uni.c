#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fffd; int rows; int* charsetpage; int (* row_byte ) (int) ;int cols; int** charset2uni; int ncharsetblocks; char* check_col_expr; char* byte_row_expr; char* byte_col_expr; TYPE_1__* charsetblocks; } ;
struct TYPE_8__ {int start; int end; } ;
typedef  TYPE_2__ Encoding ;

/* Variables and functions */
 int compact_large_charset2uni (TYPE_2__*,unsigned int**,unsigned int*) ; 
 int /*<<< orphan*/  find_charset2uni_blocks (TYPE_2__*) ; 
 int /*<<< orphan*/  find_charset2uni_pages (TYPE_2__*) ; 
 int is_charset2uni_large (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int stub1 (int) ; 
 int stub2 (int) ; 
 int stub3 (int) ; 
 int stub4 (int) ; 
 int stub5 (int) ; 
 int stub6 (int) ; 
 int stub7 (int) ; 
 int stub8 (int) ; 

__attribute__((used)) static void output_charset2uni (const char* name, Encoding* enc)
{
  int nurows, row, col, lastrow, col_max, i, i1_min, i1_max;
  bool is_large;
  unsigned int* urows;
  unsigned int urowshift;
  Encoding tmpenc;

  is_large = is_charset2uni_large(enc);
  if (is_large) {
    /* Use a temporary copy of enc. */
    tmpenc = *enc;
    enc = &tmpenc;
    nurows = compact_large_charset2uni(enc,&urows,&urowshift);
  } else {
    nurows = 0; urows = NULL; urowshift = 0; enc->fffd = 0xfffd;
  }

  find_charset2uni_pages(enc);

  find_charset2uni_blocks(enc);

  for (row = 0; row < enc->rows; row++)
    if (enc->charsetpage[row] > 0) {
      if (row == 0 || enc->charsetpage[row-1] == 0) {
        /* Start a new block. */
        for (lastrow = row; enc->charsetpage[lastrow+1] > 0; lastrow++);
        printf("static const unsigned short %s_2uni_page%02x[%d] = {\n",
               name, enc->row_byte(row),
               (lastrow-row) * enc->cols + enc->charsetpage[lastrow]);
      }
      printf("  /""* 0x%02x *""/\n ", enc->row_byte(row));
      col_max = (enc->charsetpage[row+1] > 0 ? enc->cols : enc->charsetpage[row]);
      for (col = 0; col < col_max; col++) {
        printf(" 0x%04x,", enc->charset2uni[row][col]);
        if ((col % 8) == 7 && (col+1 < col_max)) printf("\n ");
      }
      printf("\n");
      if (enc->charsetpage[row+1] == 0) {
        /* End a block. */
        printf("};\n");
      }
    }
  printf("\n");

  if (is_large) {
    printf("static const ucs4_t %s_2uni_upages[%d] = {\n ", name, nurows);
    for (i = 0; i < nurows; i++) {
      printf(" 0x%05x,", urows[i] << urowshift);
      if ((i % 8) == 7 && (i+1 < nurows)) printf("\n ");
    }
    printf("\n");
    printf("};\n");
    printf("\n");
  }

  printf("static int\n");
  printf("%s_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n)\n", name);
  printf("{\n");
  printf("  unsigned char c1 = s[0];\n");
  printf("  if (");
  for (i = 0; i < enc->ncharsetblocks; i++) {
    i1_min = enc->row_byte(enc->charsetblocks[i].start / enc->cols);
    i1_max = enc->row_byte((enc->charsetblocks[i].end-1) / enc->cols);
    if (i > 0)
      printf(" || ");
    if (i1_min == i1_max)
      printf("(c1 == 0x%02x)", i1_min);
    else
      printf("(c1 >= 0x%02x && c1 <= 0x%02x)", i1_min, i1_max);
  }
  printf(") {\n");
  printf("    if (n >= 2) {\n");
  printf("      unsigned char c2 = s[1];\n");
  printf("      if (");
  printf(enc->check_col_expr, "c2");
  printf(") {\n");
  printf("        unsigned int i = %d * (", enc->cols);
  printf(enc->byte_row_expr, "c1");
  printf(") + (");
  printf(enc->byte_col_expr, "c2");
  printf(");\n");
  printf("        %s wc = 0xfffd;\n", is_large ? "ucs4_t" : "unsigned short");
  if (is_large) printf("        unsigned short swc;\n");
  for (i = 0; i < enc->ncharsetblocks; i++) {
    printf("        ");
    if (i > 0)
      printf("} else ");
    if (i < enc->ncharsetblocks-1)
      printf("if (i < %d) ", enc->charsetblocks[i+1].start);
    printf("{\n");
    printf("          if (i < %d)\n", enc->charsetblocks[i].end);
    printf("            %s = ", is_large ? "swc" : "wc");
    printf("%s_2uni_page%02x[i", name, enc->row_byte(enc->charsetblocks[i].start / enc->cols));
    if (enc->charsetblocks[i].start > 0)
      printf("-%d", enc->charsetblocks[i].start);
    printf("]");
    if (is_large) printf(",\n            wc = %s_2uni_upages[swc>>%d] | (swc & 0x%x)", name, urowshift, (1 << urowshift) - 1);
    printf(";\n");
  }
  printf("        }\n");
  printf("        if (wc != 0xfffd) {\n");
  printf("          *pwc = %swc;\n", is_large ? "" : "(ucs4_t) ");
  printf("          return 2;\n");
  printf("        }\n");
  printf("      }\n");
  printf("      return RET_ILSEQ;\n");
  printf("    }\n");
  printf("    return RET_TOOFEW(0);\n");
  printf("  }\n");
  printf("  return RET_ILSEQ;\n");
  printf("}\n");
  printf("\n");
}