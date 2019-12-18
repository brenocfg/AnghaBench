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
 int WL_NOISE ; 
 int WL_SIGMAX ; 

__attribute__((used)) static int level_to_qual(int level)
{
	int qual = 100 * (level - WL_NOISE) / (WL_SIGMAX - WL_NOISE);
	return qual >= 0 ? (qual <= 100 ? qual : 100) : 0;
}