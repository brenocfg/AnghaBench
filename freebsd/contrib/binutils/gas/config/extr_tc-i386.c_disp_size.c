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
 int Disp16 ; 
 int Disp64 ; 
 int Disp8 ; 
 TYPE_1__ i ; 

__attribute__((used)) static int
disp_size (unsigned int n)
{
  int size = 4;
  if (i.types[n] & (Disp8 | Disp16 | Disp64))
    {
      size = 2;
      if (i.types[n] & Disp8)
	size = 1;
      if (i.types[n] & Disp64)
	size = 8;
    }
  return size;
}