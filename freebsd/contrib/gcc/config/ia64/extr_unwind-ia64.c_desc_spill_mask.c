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
struct unw_state_record {unsigned char* imask; int region_len; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned char *
desc_spill_mask (unsigned char *imaskp, struct unw_state_record *sr)
{
  sr->imask = imaskp;
  return imaskp + (2*sr->region_len + 7)/8;
}