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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int RX_Q_ENTRY_LENGTH_MASK ; 

__attribute__((used)) static inline u16 rx_q_entry_to_length (u32 x) {
  return x & RX_Q_ENTRY_LENGTH_MASK;
}