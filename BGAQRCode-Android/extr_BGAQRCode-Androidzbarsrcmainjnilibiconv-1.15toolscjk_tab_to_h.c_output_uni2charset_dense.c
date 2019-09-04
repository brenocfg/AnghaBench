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
struct TYPE_3__ {int rows; int cols; int** charset2uni; int* uni2charset; } ;
typedef  TYPE_1__ Encoding ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void output_uni2charset_dense (const char* name, Encoding* enc)
{
  /* Like in 8bit_tab_to_h.c */
  bool pages[0x300];
  int line[0x6000];
  int tableno;
  struct { int minline; int maxline; int usecount; } tables[0x6000];
  bool first;
  int row, col, j, p, j1, j2, t;

  for (p = 0; p < 0x300; p++)
    pages[p] = false;
  for (row = 0; row < enc->rows; row++)
    for (col = 0; col < enc->cols; col++) {
      j = enc->charset2uni[row][col];
      if (j != 0xfffd)
        pages[j>>8] = true;
    }
  for (j1 = 0; j1 < 0x6000; j1++) {
    bool all_invalid = true;
    for (j2 = 0; j2 < 8; j2++) {
      j = 8*j1+j2;
      if (enc->uni2charset[j] != 0)
        all_invalid = false;
    }
    if (all_invalid)
      line[j1] = -1;
    else
      line[j1] = 0;
  }
  tableno = 0;
  for (j1 = 0; j1 < 0x6000; j1++) {
    if (line[j1] >= 0) {
      if (tableno > 0
          && ((j1 > 0 && line[j1-1] == tableno-1)
              || ((tables[tableno-1].maxline >> 5) == (j1 >> 5)
                  && j1 - tables[tableno-1].maxline <= 8))) {
        line[j1] = tableno-1;
        tables[tableno-1].maxline = j1;
      } else {
        tableno++;
        line[j1] = tableno-1;
        tables[tableno-1].minline = tables[tableno-1].maxline = j1;
      }
    }
  }
  for (t = 0; t < tableno; t++) {
    tables[t].usecount = 0;
    j1 = 8*tables[t].minline;
    j2 = 8*(tables[t].maxline+1);
    for (j = j1; j < j2; j++)
      if (enc->uni2charset[j] != 0)
        tables[t].usecount++;
  }
  {
    p = -1;
    for (t = 0; t < tableno; t++)
      if (tables[t].usecount > 1) {
        p = tables[t].minline >> 5;
        printf("static const unsigned short %s_page%02x[%d] = {\n", name, p, 8*(tables[t].maxline-tables[t].minline+1));
        for (j1 = tables[t].minline; j1 <= tables[t].maxline; j1++) {
          if ((j1 % 0x20) == 0 && j1 > tables[t].minline)
            printf("  /* 0x%04x */\n", 8*j1);
          printf(" ");
          for (j2 = 0; j2 < 8; j2++) {
            j = 8*j1+j2;
            printf(" 0x%04x,", enc->uni2charset[j]);
          }
          printf(" /*0x%02x-0x%02x*/\n", 8*(j1 % 0x20), 8*(j1 % 0x20)+7);
        }
        printf("};\n");
      }
    if (p >= 0)
      printf("\n");
  }
  printf("static int\n%s_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)\n", name);
  printf("{\n");
  printf("  if (n >= 2) {\n");
  printf("    unsigned short c = 0;\n");
  first = true;
  for (j1 = 0; j1 < 0x6000;) {
    t = line[j1];
    for (j2 = j1; j2 < 0x6000 && line[j2] == t; j2++);
    if (t >= 0) {
      if (j1 != tables[t].minline) abort();
      if (j2 > tables[t].maxline+1) abort();
      j2 = tables[t].maxline+1;
      if (first)
        printf("    ");
      else
        printf("    else ");
      first = false;
      if (tables[t].usecount == 0) abort();
      if (tables[t].usecount == 1) {
        if (j2 != j1+1) abort();
        for (j = 8*j1; j < 8*j2; j++)
          if (enc->uni2charset[j] != 0) {
            printf("if (wc == 0x%04x)\n      c = 0x%02x;\n", j, enc->uni2charset[j]);
            break;
          }
      } else {
        if (j1 == 0) {
          printf("if (wc < 0x%04x)", 8*j2);
        } else {
          printf("if (wc >= 0x%04x && wc < 0x%04x)", 8*j1, 8*j2);
        }
        printf("\n      c = %s_page%02x[wc", name, j1 >> 5);
        if (tables[t].minline > 0)
          printf("-0x%04x", 8*j1);
        printf("];\n");
      }
    }
    j1 = j2;
  }
  printf("    if (c != 0) {\n");
  printf("      r[0] = (c >> 8); r[1] = (c & 0xff);\n");
  printf("      return 2;\n");
  printf("    }\n");
  printf("    return RET_ILUNI;\n");
  printf("  }\n");
  printf("  return RET_TOOSMALL;\n");
  printf("}\n");
}