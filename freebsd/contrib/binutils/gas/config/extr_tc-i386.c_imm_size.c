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
struct TYPE_2__ {int* types; } ;

/* Variables and functions */
 int Imm16 ; 
 int Imm64 ; 
 int Imm8 ; 
 int Imm8S ; 
 TYPE_1__ i ; 

__attribute__((used)) static int
imm_size (unsigned int n)
{
  int size = 4;
  if (i.types[n] & (Imm8 | Imm8S | Imm16 | Imm64))
    {
      size = 2;
      if (i.types[n] & (Imm8 | Imm8S))
	size = 1;
      if (i.types[n] & Imm64)
	size = 8;
    }
  return size;
}