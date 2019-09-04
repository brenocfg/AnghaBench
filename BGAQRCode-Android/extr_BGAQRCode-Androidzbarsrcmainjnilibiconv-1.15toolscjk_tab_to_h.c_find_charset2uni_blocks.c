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
struct TYPE_5__ {int start; scalar_t__ end; } ;
struct TYPE_4__ {int rows; scalar_t__* charsetpage; int cols; int ncharsetblocks; TYPE_2__* charsetblocks; } ;
typedef  TYPE_1__ Encoding ;
typedef  TYPE_2__ Block ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

__attribute__((used)) static void find_charset2uni_blocks (Encoding* enc)
{
  int n, row, lastrow;

  enc->charsetblocks = (Block*) malloc(enc->rows*sizeof(Block));

  n = 0;
  for (row = 0; row < enc->rows; row++)
    if (enc->charsetpage[row] > 0 && (row == 0 || enc->charsetpage[row-1] == 0)) {
      for (lastrow = row; enc->charsetpage[lastrow+1] > 0; lastrow++);
      enc->charsetblocks[n].start = row * enc->cols;
      enc->charsetblocks[n].end = lastrow * enc->cols + enc->charsetpage[lastrow];
      n++;
    }
  enc->ncharsetblocks = n;
}