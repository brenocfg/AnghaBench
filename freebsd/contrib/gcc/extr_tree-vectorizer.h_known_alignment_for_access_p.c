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
struct data_reference {int dummy; } ;

/* Variables and functions */
 int DR_MISALIGNMENT (struct data_reference*) ; 

__attribute__((used)) static inline bool
known_alignment_for_access_p (struct data_reference *data_ref_info)
{
  return (DR_MISALIGNMENT (data_ref_info) != -1);
}