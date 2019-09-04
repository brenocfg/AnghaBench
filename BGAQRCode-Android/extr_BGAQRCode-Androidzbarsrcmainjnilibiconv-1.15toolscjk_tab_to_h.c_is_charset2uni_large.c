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
struct TYPE_3__ {int rows; int cols; int** charset2uni; } ;
typedef  TYPE_1__ Encoding ;

/* Variables and functions */

__attribute__((used)) static bool is_charset2uni_large (Encoding* enc)
{
  int row, col;

  for (row = 0; row < enc->rows; row++)
    for (col = 0; col < enc->cols; col++)
      if (enc->charset2uni[row][col] >= 0x10000)
        return true;
  return false;
}