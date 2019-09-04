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
struct TYPE_3__ {int* uni2charset; int rows; int cols; int** charset2uni; int (* row_byte ) (int) ;int (* col_byte ) (int) ;} ;
typedef  TYPE_1__ Encoding ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int stub1 (int) ; 
 int stub2 (int) ; 

__attribute__((used)) static void invert (Encoding* enc)
{
  int row, col, j;

  enc->uni2charset = (int*) malloc(0x30000*sizeof(int));

  for (j = 0; j < 0x30000; j++)
    enc->uni2charset[j] = 0;

  for (row = 0; row < enc->rows; row++)
    for (col = 0; col < enc->cols; col++) {
      j = enc->charset2uni[row][col];
      if (j != 0xfffd)
        enc->uni2charset[j] = 0x100 * enc->row_byte(row) + enc->col_byte(col);
    }
}