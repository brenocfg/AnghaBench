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

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int scanf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_gb18030uni (const char* name)
{
  int c;
  unsigned int bytes;
  int i1, i2, i3, i4, i, j, k;
  int charset2uni[4*10*126*10];
  int uni2charset[0x10000];
  struct { int low; int high; int diff; int total; } ranges[256];
  int ranges_count, ranges_total;

  for (i = 0; i < 4*10*126*10; i++)
    charset2uni[i] = 0;
  for (j = 0; j < 0x10000; j++)
    uni2charset[j] = 0;

  /* Read a unicode.org style .TXT file. */
  for (;;) {
    c = getc(stdin);
    if (c == EOF)
      break;
    if (c == '\n' || c == ' ' || c == '\t')
      continue;
    if (c == '#') {
      do { c = getc(stdin); } while (!(c == EOF || c == '\n'));
      continue;
    }
    ungetc(c,stdin);
    if (scanf("0x%x", &bytes) != 1)
      exit(1);
    i1 = (bytes >> 24) & 0xff;
    i2 = (bytes >> 16) & 0xff;
    i3 = (bytes >> 8) & 0xff;
    i4 = bytes & 0xff;
    if (!(i1 >= 0x81 && i1 <= 0x84
          && i2 >= 0x30 && i2 <= 0x39
          && i3 >= 0x81 && i3 <= 0xfe
          && i4 >= 0x30 && i4 <= 0x39)) {
      fprintf(stderr, "lost entry for %02x %02x %02x %02x\n", i1, i2, i3, i4);
      exit(1);
    }
    i = (((i1-0x81) * 10 + (i2-0x30)) * 126 + (i3-0x81)) * 10 + (i4-0x30);
    if (scanf(" 0x%x", &j) != 1)
      exit(1);
    if (!(j >= 0 && j < 0x10000))
      exit(1);
    charset2uni[i] = j;
    uni2charset[j] = i;
  }

  /* Verify that the mapping i -> j is monotonically increasing and
     of the form
        low[k] <= i <= high[k]  =>  j = diff[k] + i
     with a set of disjoint intervals (low[k], high[k]). */
  ranges_count = 0;
  for (i = 0; i < 4*10*126*10; i++)
    if (charset2uni[i] != 0) {
      int diff;
      j = charset2uni[i];
      diff = j - i;
      if (ranges_count > 0) {
        if (!(i > ranges[ranges_count-1].high))
          exit(1);
        if (!(j > ranges[ranges_count-1].high + ranges[ranges_count-1].diff))
          exit(1);
        /* Additional property: The diffs are also increasing. */
        if (!(diff >= ranges[ranges_count-1].diff))
          exit(1);
      }
      if (ranges_count > 0 && diff == ranges[ranges_count-1].diff)
        ranges[ranges_count-1].high = i;
      else {
        if (ranges_count == 256)
          exit(1);
        ranges[ranges_count].low = i;
        ranges[ranges_count].high = i;
        ranges[ranges_count].diff = diff;
        ranges_count++;
      }
    }

  /* Determine size of bitmap. */
  ranges_total = 0;
  for (k = 0; k < ranges_count; k++) {
    ranges[k].total = ranges_total;
    ranges_total += ranges[k].high - ranges[k].low + 1;
  }

  printf("static const unsigned short %s_charset2uni_ranges[%d] = {\n", name, 2*ranges_count);
  for (k = 0; k < ranges_count; k++) {
    printf("  0x%04x, 0x%04x", ranges[k].low, ranges[k].high);
    if (k+1 < ranges_count) printf(",");
    if ((k % 4) == 3 && k+1 < ranges_count) printf("\n");
  }
  printf("\n");
  printf("};\n");

  printf("\n");

  printf("static const unsigned short %s_uni2charset_ranges[%d] = {\n", name, 2*ranges_count);
  for (k = 0; k < ranges_count; k++) {
    printf("  0x%04x, 0x%04x", ranges[k].low + ranges[k].diff, ranges[k].high + ranges[k].diff);
    if (k+1 < ranges_count) printf(",");
    if ((k % 4) == 3 && k+1 < ranges_count) printf("\n");
  }
  printf("\n");
  printf("};\n");

  printf("\n");

  printf("static const struct { unsigned short diff; unsigned short bitmap_offset; } %s_ranges[%d] = {\n ", name, ranges_count);
  for (k = 0; k < ranges_count; k++) {
    printf(" { %5d, 0x%04x }", ranges[k].diff, ranges[k].total);
    if (k+1 < ranges_count) printf(",");
    if ((k % 4) == 3 && k+1 < ranges_count) printf("\n ");
  }
  printf("\n");
  printf("};\n");

  printf("\n");

  printf("static const unsigned char %s_bitmap[%d] = {\n ", name, (ranges_total + 7) / 8);
  {
    int accu = 0;
    for (k = 0; k < ranges_count; k++) {
      for (i = ranges[k].total; i <= ranges[k].total + (ranges[k].high - ranges[k].low);) {
        if (charset2uni[i - ranges[k].total + ranges[k].low] != 0)
          accu |= (1 << (i % 8));
        i++;
        if ((i % 8) == 0) {
          printf(" 0x%02x", accu);
          if ((i / 8) < (ranges_total + 7) / 8) printf(",");
          if (((i / 8) % 12) == 0)
            printf("\n ");
          accu = 0;
        }
      }
      if (i != (k+1 < ranges_count ? ranges[k+1].total : ranges_total)) abort();
    }
    if ((ranges_total % 8) != 0)
      printf(" 0x%02x", accu);
    printf("\n");
  }
  printf("};\n");

  printf("\n");

  printf("static int\n");
  printf("%s_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n)\n", name);
  printf("{\n");
  printf("  unsigned char c1 = s[0];\n");
  printf("  if (c1 >= 0x81 && c1 <= 0x84) {\n");
  printf("    if (n >= 2) {\n");
  printf("      unsigned char c2 = s[1];\n");
  printf("      if (c2 >= 0x30 && c2 <= 0x39) {\n");
  printf("        if (n >= 3) {\n");
  printf("          unsigned char c3 = s[2];\n");
  printf("          if (c3 >= 0x81 && c3 <= 0xfe) {\n");
  printf("            if (n >= 4) {\n");
  printf("              unsigned char c4 = s[3];\n");
  printf("              if (c4 >= 0x30 && c4 <= 0x39) {\n");
  printf("                unsigned int i = (((c1 - 0x81) * 10 + (c2 - 0x30)) * 126 + (c3 - 0x81)) * 10 + (c4 - 0x30);\n");
  printf("                if (i >= %d && i <= %d) {\n", ranges[0].low, ranges[ranges_count-1].high);
  printf("                  unsigned int k1 = 0;\n");
  printf("                  unsigned int k2 = %d;\n", ranges_count-1);
  printf("                  while (k1 < k2) {\n");
  printf("                    unsigned int k = (k1 + k2) / 2;\n");
  printf("                    if (i <= %s_charset2uni_ranges[2*k+1])\n", name);
  printf("                      k2 = k;\n");
  printf("                    else if (i >= %s_charset2uni_ranges[2*k+2])\n", name);
  printf("                      k1 = k + 1;\n");
  printf("                    else\n");
  printf("                      return RET_ILSEQ;\n");
  printf("                  }\n");
  printf("                  {\n");
  printf("                    unsigned int bitmap_index = i - %s_charset2uni_ranges[2*k1] + %s_ranges[k1].bitmap_offset;\n", name, name);
  printf("                    if ((%s_bitmap[bitmap_index >> 3] >> (bitmap_index & 7)) & 1) {\n", name);
  printf("                      unsigned int diff = %s_ranges[k1].diff;\n", name);
  printf("                      *pwc = (ucs4_t) (i + diff);\n");
  printf("                      return 4;\n");
  printf("                    }\n");
  printf("                  }\n");
  printf("                }\n");
  printf("              }\n");
  printf("              return RET_ILSEQ;\n");
  printf("            }\n");
  printf("            return RET_TOOFEW(0);\n");
  printf("          }\n");
  printf("          return RET_ILSEQ;\n");
  printf("        }\n");
  printf("        return RET_TOOFEW(0);\n");
  printf("      }\n");
  printf("      return RET_ILSEQ;\n");
  printf("    }\n");
  printf("    return RET_TOOFEW(0);\n");
  printf("  }\n");
  printf("  return RET_ILSEQ;\n");
  printf("}\n");

  printf("\n");

  printf("static int\n");
  printf("%s_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)\n", name);
  printf("{\n");
  printf("  if (n >= 4) {\n");
  printf("    unsigned int i = wc;\n");
  printf("    if (i >= 0x%04x && i <= 0x%04x) {\n", ranges[0].low + ranges[0].diff, ranges[ranges_count-1].high + ranges[ranges_count-1].diff);
  printf("      unsigned int k1 = 0;\n");
  printf("      unsigned int k2 = %d;\n", ranges_count-1);
  printf("      while (k1 < k2) {\n");
  printf("        unsigned int k = (k1 + k2) / 2;\n");
  printf("        if (i <= %s_uni2charset_ranges[2*k+1])\n", name);
  printf("          k2 = k;\n");
  printf("        else if (i >= %s_uni2charset_ranges[2*k+2])\n", name);
  printf("          k1 = k + 1;\n");
  printf("        else\n");
  printf("          return RET_ILUNI;\n");
  printf("      }\n");
  printf("      {\n");
  printf("        unsigned int bitmap_index = i - %s_uni2charset_ranges[2*k1] + %s_ranges[k1].bitmap_offset;\n", name, name);
  printf("        if ((%s_bitmap[bitmap_index >> 3] >> (bitmap_index & 7)) & 1) {\n", name);
  printf("          unsigned int diff = %s_ranges[k1].diff;\n", name);
  printf("          i -= diff;\n");
  printf("          r[3] = (i %% 10) + 0x30; i = i / 10;\n");
  printf("          r[2] = (i %% 126) + 0x81; i = i / 126;\n");
  printf("          r[1] = (i %% 10) + 0x30; i = i / 10;\n");
  printf("          r[0] = i + 0x81;\n");
  printf("          return 4;\n");
  printf("        }\n");
  printf("      }\n");
  printf("    }\n");
  printf("    return RET_ILUNI;\n");
  printf("  }\n");
  printf("  return RET_TOOSMALL;\n");
  printf("}\n");
}