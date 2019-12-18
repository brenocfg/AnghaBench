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
typedef  int qsize_t ;

/* Variables and functions */
 int QUOTABLOCK_BITS ; 

__attribute__((used)) static inline qsize_t v1_qbtos(qsize_t blocks)
{
	return blocks << QUOTABLOCK_BITS;
}