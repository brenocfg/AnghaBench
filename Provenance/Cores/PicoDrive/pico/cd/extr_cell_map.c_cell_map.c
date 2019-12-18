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

__attribute__((used)) static unsigned int cell_map(int celln)
{
  int col, row;

  switch ((celln >> 12) & 7) { // 0-0x8000
    case 0: // x32 cells
    case 1:
    case 2:
    case 3:
      col = celln >> 8;
      row = celln & 0xff;
      break;
    case 4: // x16
    case 5:
      col  = celln >> 7;
      row  = celln & 0x7f;
      row |= 0x10000 >> 8;
      break;
    case 6: // x8
      col  = celln >> 6;
      row  = celln & 0x3f;
      row |= 0x18000 >> 8;
      break;
    case 7: // x4
      col  = celln >> 5;
      row  = celln & 0x1f;
      row |= (celln & 0x7800) >> 6;
      break;
    default: // never happens, only here to make compiler happy
      col = row = 0;
      break;
  }

  return (col & 0x3f) + row*64;
}