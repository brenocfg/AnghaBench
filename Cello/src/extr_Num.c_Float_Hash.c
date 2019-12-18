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
typedef  int /*<<< orphan*/  var ;
union interp_cast {int /*<<< orphan*/  as_int; int /*<<< orphan*/  as_flt; } ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  c_float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t Float_Hash(var self) {
  union interp_cast ic;
  ic.as_flt = c_float(self);
  return ic.as_int;
}