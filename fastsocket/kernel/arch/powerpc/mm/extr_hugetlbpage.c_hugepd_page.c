#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_3__ {int pd; } ;
typedef  TYPE_1__ hugepd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HUGEPD_OK ; 

__attribute__((used)) static inline pte_t *hugepd_page(hugepd_t hpd)
{
	BUG_ON(!(hpd.pd & HUGEPD_OK));
	return (pte_t *)(hpd.pd & ~HUGEPD_OK);
}