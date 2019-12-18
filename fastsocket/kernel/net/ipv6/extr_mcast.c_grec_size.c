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
struct mld2_grec {int dummy; } ;
struct ifmcaddr6 {int dummy; } ;

/* Variables and functions */
 int mld_scount (struct ifmcaddr6*,int,int,int) ; 

__attribute__((used)) static int grec_size(struct ifmcaddr6 *pmc, int type, int gdel, int sdel)
{
	return sizeof(struct mld2_grec) + 16 * mld_scount(pmc,type,gdel,sdel);
}