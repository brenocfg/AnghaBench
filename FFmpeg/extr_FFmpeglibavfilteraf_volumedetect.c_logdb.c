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
typedef  double uint64_t ;

/* Variables and functions */
 double MAX_DB ; 
 int log10 (double) ; 

__attribute__((used)) static inline double logdb(uint64_t v)
{
    double d = v / (double)(0x8000 * 0x8000);
    if (!v)
        return MAX_DB;
    return -log10(d) * 10;
}