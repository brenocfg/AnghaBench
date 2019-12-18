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
struct pm2fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM2R_IN_FIFO_SPACE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ pm2_RD (struct pm2fb_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void WAIT_FIFO(struct pm2fb_par *p, u32 a)
{
	while (pm2_RD(p, PM2R_IN_FIFO_SPACE) < a)
		cpu_relax();
}