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
typedef  int u16 ;
struct dcb_output {int extdev; int location; int type; } ;

/* Variables and functions */

__attribute__((used)) static inline u16
dcb_outp_hasht(struct dcb_output *outp)
{
	return (outp->extdev << 8) | (outp->location << 4) | outp->type;
}