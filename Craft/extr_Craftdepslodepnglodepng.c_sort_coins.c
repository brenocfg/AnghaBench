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
struct TYPE_3__ {float weight; int /*<<< orphan*/  symbols; } ;
typedef  TYPE_1__ Coin ;

/* Variables and functions */
 int /*<<< orphan*/  uivector_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sort_coins(Coin* data, size_t amount)
{
  size_t gap = amount;
  unsigned char swapped = 0;
  while((gap > 1) || swapped)
  {
    size_t i;
    gap = (gap * 10) / 13; /*shrink factor 1.3*/
    if(gap == 9 || gap == 10) gap = 11; /*combsort11*/
    if(gap < 1) gap = 1;
    swapped = 0;
    for(i = 0; i < amount - gap; i++)
    {
      size_t j = i + gap;
      if(data[j].weight < data[i].weight)
      {
        float temp = data[j].weight; data[j].weight = data[i].weight; data[i].weight = temp;
        uivector_swap(&data[i].symbols, &data[j].symbols);
        swapped = 1;
      }
    }
  }
}