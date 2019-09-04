#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int start; int end; } ;
struct TYPE_4__ {int rows; int cols; int** charset2uni; int* uni2charset; } ;
typedef  TYPE_1__ Encoding ;
typedef  TYPE_2__ Block ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void output_uni2charset_sparse (const char* name, Encoding* enc, bool monotonic)
{
  bool pages[0x300];
  Block pageblocks[0x300]; int npageblocks;
  int indx2charset[0x30000];
  int summary_indx[0x3000];
  int summary_used[0x3000];
  int i, row, col, j, p, j1, j2, indx;
  bool is_large;
  /* for monotonic: */
  int log2_stepsize = (!strcmp(name,"uhc_2") ? 6 : 7);
  int stepsize = 1 << log2_stepsize;
  int indxsteps;

  /* Fill pages[0x300]. */
  for (p = 0; p < 0x300; p++)
    pages[p] = false;
  for (row = 0; row < enc->rows; row++)
    for (col = 0; col < enc->cols; col++) {
      j = enc->charset2uni[row][col];
      if (j != 0xfffd)
        pages[j>>8] = true;
    }

  /* Determine whether two or three bytes are needed for each character. */
  is_large = false;
  for (j = 0; j < 0x30000; j++)
    if (enc->uni2charset[j] >= 0x10000)
      is_large = true;

#if 0
  for (p = 0; p < 0x300; p++)
    if (pages[p]) {
      printf("static const unsigned short %s_page%02x[256] = {\n", name, p);
      for (j1 = 0; j1 < 32; j1++) {
        printf("  ");
        for (j2 = 0; j2 < 8; j2++)
          printf("0x%04x, ", enc->uni2charset[256*p+8*j1+j2]);
        printf("/""*0x%02x-0x%02x*""/\n", 8*j1, 8*j1+7);
      }
      printf("};\n");
    }
  printf("\n");
#endif

  /* Fill summary_indx[] and summary_used[]. */
  indx = 0;
  for (j1 = 0; j1 < 0x3000; j1++) {
    summary_indx[j1] = indx;
    summary_used[j1] = 0;
    for (j2 = 0; j2 < 16; j2++) {
      j = 16*j1+j2;
      if (enc->uni2charset[j] != 0) {
        indx2charset[indx++] = enc->uni2charset[j];
        summary_used[j1] |= (1 << j2);
      }
    }
  }

  /* Fill npageblocks and pageblocks[]. */
  npageblocks = 0;
  for (p = 0; p < 0x300; ) {
    if (pages[p] && (p == 0 || !pages[p-1])) {
      pageblocks[npageblocks].start = 16*p;
      do p++; while (p < 0x300 && pages[p]);
      j1 = 16*p;
      while (summary_used[j1-1] == 0) j1--;
      pageblocks[npageblocks].end = j1;
      npageblocks++;
    } else
      p++;
  }

  if (monotonic) {
    indxsteps = (indx + stepsize-1) / stepsize;
    printf("static const unsigned short %s_2charset_main[%d] = {\n", name, indxsteps);
    for (i = 0; i < indxsteps; ) {
      if ((i % 8) == 0) printf(" ");
      printf(" 0x%04x,", indx2charset[i*stepsize]);
      i++;
      if ((i % 8) == 0 || i == indxsteps) printf("\n");
    }
    printf("};\n");
    printf("static const unsigned char %s_2charset[%d] = {\n", name, indx);
    for (i = 0; i < indx; ) {
      if ((i % 8) == 0) printf(" ");
      printf(" 0x%02x,", indx2charset[i] - indx2charset[i/stepsize*stepsize]);
      i++;
      if ((i % 8) == 0 || i == indx) printf("\n");
    }
    printf("};\n");
  } else {
    if (is_large) {
      printf("static const unsigned char %s_2charset[3*%d] = {\n", name, indx);
      for (i = 0; i < indx; ) {
        if ((i % 4) == 0) printf(" ");
        printf(" 0x%1x,0x%02x,0x%02x,", indx2charset[i] >> 16,
               (indx2charset[i] >> 8) & 0xff, indx2charset[i] & 0xff);
        i++;
        if ((i % 4) == 0 || i == indx) printf("\n");
      }
      printf("};\n");
    } else {
      printf("static const unsigned short %s_2charset[%d] = {\n", name, indx);
      for (i = 0; i < indx; ) {
        if ((i % 8) == 0) printf(" ");
        printf(" 0x%04x,", indx2charset[i]);
        i++;
        if ((i % 8) == 0 || i == indx) printf("\n");
      }
      printf("};\n");
    }
  }
  printf("\n");
  for (i = 0; i < npageblocks; i++) {
    printf("static const Summary16 %s_uni2indx_page%02x[%d] = {\n", name,
           pageblocks[i].start/16, pageblocks[i].end-pageblocks[i].start);
    for (j1 = pageblocks[i].start; j1 < pageblocks[i].end; ) {
      if (((16*j1) % 0x100) == 0) printf("  /""* 0x%04x *""/\n", 16*j1);
      if ((j1 % 4) == 0) printf(" ");
      printf(" { %4d, 0x%04x },", summary_indx[j1], summary_used[j1]);
      j1++;
      if ((j1 % 4) == 0 || j1 == pageblocks[i].end) printf("\n");
    }
    printf("};\n");
  }
  printf("\n");

  printf("static int\n");
  printf("%s_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)\n", name);
  printf("{\n");
  printf("  if (n >= 2) {\n");
  printf("    const Summary16 *summary = NULL;\n");
  for (i = 0; i < npageblocks; i++) {
    printf("    ");
    if (i > 0)
      printf("else ");
    printf("if (wc >= 0x%04x && wc < 0x%04x)\n",
           16*pageblocks[i].start, 16*pageblocks[i].end);
    printf("      summary = &%s_uni2indx_page%02x[(wc>>4)", name,
           pageblocks[i].start/16);
    if (pageblocks[i].start > 0)
      printf("-0x%03x", pageblocks[i].start);
    printf("];\n");
  }
  printf("    if (summary) {\n");
  printf("      unsigned short used = summary->used;\n");
  printf("      unsigned int i = wc & 0x0f;\n");
  printf("      if (used & ((unsigned short) 1 << i)) {\n");
  if (monotonic || !is_large)
    printf("        unsigned short c;\n");
  printf("        /* Keep in 'used' only the bits 0..i-1. */\n");
  printf("        used &= ((unsigned short) 1 << i) - 1;\n");
  printf("        /* Add 'summary->indx' and the number of bits set in 'used'. */\n");
  printf("        used = (used & 0x5555) + ((used & 0xaaaa) >> 1);\n");
  printf("        used = (used & 0x3333) + ((used & 0xcccc) >> 2);\n");
  printf("        used = (used & 0x0f0f) + ((used & 0xf0f0) >> 4);\n");
  printf("        used = (used & 0x00ff) + (used >> 8);\n");
  if (monotonic) {
    printf("        used += summary->indx;\n");
    printf("        c = %s_2charset_main[used>>%d] + %s_2charset[used];\n", name, log2_stepsize, name);
    printf("        r[0] = (c >> 8); r[1] = (c & 0xff);\n");
    printf("        return 2;\n");
  } else {
    if (is_large) {
      printf("        used += summary->indx;\n");
      printf("        r[0] = %s_2charset[3*used];\n", name);
      printf("        r[1] = %s_2charset[3*used+1];\n", name);
      printf("        r[2] = %s_2charset[3*used+2];\n", name);
      printf("        return 3;\n");
    } else {
      printf("        c = %s_2charset[summary->indx + used];\n", name);
      printf("        r[0] = (c >> 8); r[1] = (c & 0xff);\n");
      printf("        return 2;\n");
    }
  }
  printf("      }\n");
  printf("    }\n");
  printf("    return RET_ILUNI;\n");
  printf("  }\n");
  printf("  return RET_TOOSMALL;\n");
  printf("}\n");
}