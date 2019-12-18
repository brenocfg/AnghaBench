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
struct pacct_struct {int /*<<< orphan*/  ac_stime; int /*<<< orphan*/  ac_utime; } ;

/* Variables and functions */
 int /*<<< orphan*/  cputime_zero ; 
 int /*<<< orphan*/  memset (struct pacct_struct*,int /*<<< orphan*/ ,int) ; 

void acct_init_pacct(struct pacct_struct *pacct)
{
	memset(pacct, 0, sizeof(struct pacct_struct));
	pacct->ac_utime = pacct->ac_stime = cputime_zero;
}