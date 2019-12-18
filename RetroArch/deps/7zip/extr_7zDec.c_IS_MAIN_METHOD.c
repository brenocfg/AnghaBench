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
typedef  int uint32_t ;

/* Variables and functions */
#define  k_Copy 130 
#define  k_LZMA 129 
#define  k_LZMA2 128 

__attribute__((used)) static bool IS_MAIN_METHOD(uint32_t m)
{
  switch(m)
  {
    case k_Copy:
    case k_LZMA:
    case k_LZMA2:
      return true;
  }
  return false;
}