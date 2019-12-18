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

/* Variables and functions */
 int /*<<< orphan*/  pms_vert (unsigned short,unsigned short) ; 

__attribute__((used)) static void pms_vertdeci(unsigned short decinum, unsigned short deciden)
{
	/* Knock it down by /5 once */
	if(decinum%5==0)
	{
		deciden/=5;
		decinum/=5;
	}
	/*
	 *	3's
	 */
	while(decinum%3==0 && deciden%3==0)
	{
		deciden/=3;
		decinum/=3;
	}
	/*
	 *	2's
	 */
	while(decinum%2==0 && deciden%2==0)
	{
		decinum/=2;
		deciden/=2;
	}
	/*
	 *	Fudgyify
	 */
	while(deciden>32)
	{
		deciden/=2;
		decinum=(decinum+1)/2;
	}
	if(deciden==32)
		deciden--;
	pms_vert(deciden,decinum);
}