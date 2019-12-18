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
 int read64le (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double u64_to_double (int /*<<< orphan*/ ) ; 

inline int read_double_le(double *Bufo, EMUFILE*is) { uint64 temp; int ret = read64le(&temp,is); *Bufo = u64_to_double(temp); return ret; }