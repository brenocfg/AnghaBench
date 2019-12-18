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
typedef  scalar_t__ u32 ;
struct mon_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ mon_mca_end (struct mon_msg*) ; 
 scalar_t__ mon_mca_start (struct mon_msg*) ; 

__attribute__((used)) static inline u32 mon_mca_size(struct mon_msg *monmsg)
{
	return mon_mca_end(monmsg) - mon_mca_start(monmsg) + 1;
}