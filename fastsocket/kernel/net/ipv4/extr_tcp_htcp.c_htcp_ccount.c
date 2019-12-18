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
typedef  int u32 ;
struct htcp {int minRTT; } ;

/* Variables and functions */
 int htcp_cong_time (struct htcp const*) ; 

__attribute__((used)) static inline u32 htcp_ccount(const struct htcp *ca)
{
	return htcp_cong_time(ca) / ca->minRTT;
}