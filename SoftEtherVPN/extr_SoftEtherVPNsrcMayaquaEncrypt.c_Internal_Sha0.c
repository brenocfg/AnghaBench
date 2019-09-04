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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  MY_SHA0_hash (unsigned char const*,int,unsigned char*) ; 

__attribute__((used)) static void Internal_Sha0(unsigned char *dest, const unsigned char *src, const UINT size)
{
	MY_SHA0_hash(src, (int)size, dest);
}