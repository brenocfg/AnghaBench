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
struct TYPE_3__ {int** charset2uni; int rows; int cols; int (* byte_row ) (int) ;int (* byte_col ) (int) ;} ;
typedef  TYPE_1__ Encoding ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int getc (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int scanf (char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int stub1 (int) ; 
 int stub2 (int) ; 
 int stub3 (int) ; 
 int stub4 (int) ; 
 size_t stub5 (int) ; 
 size_t stub6 (int) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_table_ksc5601 (Encoding* enc)
{
  int row, col, i, i1, i2, c, j;

  enc->charset2uni = (int**) malloc(enc->rows*sizeof(int*));
  for (row = 0; row < enc->rows; row++)
    enc->charset2uni[row] = (int*) malloc(enc->cols*sizeof(int));

  for (row = 0; row < enc->rows; row++)
    for (col = 0; col < enc->cols; col++)
      enc->charset2uni[row][col] = 0xfffd;

  c = getc(stdin);
  ungetc(c,stdin);
  if (c == '#') {
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
      if (scanf("0x%x", &j) != 1)
        exit(1);
      i1 = j >> 8;
      i2 = j & 0xff;
      if (scanf(" 0x%x", &j) != 1)
        exit(1);
      /* Take only the range covered by KS C 5601.1987-0 = KS C 5601.1989-0
         = KS X 1001.1992, ignore the rest. */
      if (!(i1 >= 128+33 && i1 < 128+127 && i2 >= 128+33 && i2 < 128+127))
        continue;  /* KSC5601 specific */
      i1 &= 0x7f;  /* KSC5601 specific */
      i2 &= 0x7f;  /* KSC5601 specific */
      row = enc->byte_row(i1);
      col = enc->byte_col(i2);
      if (row < 0 || col < 0) {
        fprintf(stderr, "lost entry for %02x %02x\n", i1, i2);
        exit(1);
      }
      enc->charset2uni[row][col] = j;
    }
  } else {
    /* Read a table of hexadecimal Unicode values. */
    for (i1 = 33; i1 < 127; i1++)
      for (i2 = 33; i2 < 127; i2++) {
        i = scanf("%x", &j);
        if (i == EOF)
          goto read_done;
        if (i != 1)
          exit(1);
        if (j < 0 || j == 0xffff)
          j = 0xfffd;
        if (j != 0xfffd) {
          if (enc->byte_row(i1) < 0 || enc->byte_col(i2) < 0) {
            fprintf(stderr, "lost entry at %02x %02x\n", i1, i2);
            exit (1);
          }
          enc->charset2uni[enc->byte_row(i1)][enc->byte_col(i2)] = j;
        }
      }
   read_done: ;
  }
}