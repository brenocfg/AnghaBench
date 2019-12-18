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

/* Variables and functions */
 int flag_iso ; 
 int pedantic ; 
 int warn_pointer_arith ; 
 int warn_traditional ; 

__attribute__((used)) static inline void
restore_extension_diagnostics (int flags)
{
  pedantic = flags & 1;
  warn_pointer_arith = (flags >> 1) & 1;
  warn_traditional = (flags >> 2) & 1;
  flag_iso = (flags >> 3) & 1;
}