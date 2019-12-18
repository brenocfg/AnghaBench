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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  EMUFILE ;

/* Variables and functions */
 int /*<<< orphan*/  double_to_u64 (double) ; 
 int write64le (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

inline int write_double_le(double b, EMUFILE*is) { uint64 temp = double_to_u64(b); int ret = write64le(temp,is); return ret; }