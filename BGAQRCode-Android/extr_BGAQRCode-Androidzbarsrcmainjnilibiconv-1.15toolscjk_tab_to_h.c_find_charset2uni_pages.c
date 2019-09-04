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
struct TYPE_3__ {int* charsetpage; int rows; int cols; scalar_t__** charset2uni; scalar_t__ fffd; } ;
typedef  TYPE_1__ Encoding ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

__attribute__((used)) static void find_charset2uni_pages (Encoding* enc)
{
  int row, col;

  enc->charsetpage = (int*) malloc((enc->rows+1)*sizeof(int));

  for (row = 0; row <= enc->rows; row++)
    enc->charsetpage[row] = 0;

  for (row = 0; row < enc->rows; row++) {
    int used = 0;
    for (col = 0; col < enc->cols; col++)
      if (enc->charset2uni[row][col] != enc->fffd)
        used = col+1;
    enc->charsetpage[row] = used;
  }
}