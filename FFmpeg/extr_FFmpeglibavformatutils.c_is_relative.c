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
typedef  long long int64_t ;

/* Variables and functions */
 long long RELATIVE_TS_BASE ; 

__attribute__((used)) static int is_relative(int64_t ts) {
    return ts > (RELATIVE_TS_BASE - (1LL<<48));
}