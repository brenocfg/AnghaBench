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
struct timespec {int dummy; } ;
struct sfbbinstats {int dummy; } ;
struct sfb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 void sfb_adjust_bin (struct sfb*,struct sfbbinstats*,struct timespec*,struct timespec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sfb_increment_bin(struct sfb *sp, struct sfbbinstats *bin, struct timespec *ft,
    struct timespec *now)
{
	return (sfb_adjust_bin(sp, bin, ft, now, TRUE));
}