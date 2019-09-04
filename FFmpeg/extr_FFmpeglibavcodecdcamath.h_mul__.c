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
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int norm__ (int,int) ; 

__attribute__((used)) static inline int32_t mul__(int32_t a, int32_t b, int bits)
{
    return norm__((int64_t)a * b, bits);
}