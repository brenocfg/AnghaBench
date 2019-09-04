#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int CR; } ;

/* Variables and functions */
 TYPE_1__* HASH ; 
 int HASH_CR_NBW ; 

uint8_t HASH_GetInFIFOWordsNbr(void)
{
  /* Return the value of NBW bits */
  return ((HASH->CR & HASH_CR_NBW) >> 8);
}