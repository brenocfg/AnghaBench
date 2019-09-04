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
typedef  int UINT8 ;
typedef  unsigned long INT64 ;
typedef  int INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 

void interface_clock_changed() {
  UINT8 m_divshift;
  INT32 m_divisor;

  // INT64 attos = m_attoseconds_per_cycle;
  INT64 attos = 279365114840;
  m_divshift = 0;
  while (attos >= (1UL << 31)) {
    m_divshift++;
    printf("m_divshift is %i, on %lld >?= %lu\n", m_divshift, attos, 1UL << 31);
    attos >>= 1;
  }
  m_divisor = attos;

  printf("m_divisor is %i\n", m_divisor);
}