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
typedef  int u_int32_t ;

/* Variables and functions */
 int inaddr_hashp ; 
 int inaddr_nhash ; 

u_int32_t
inaddr_hashval(u_int32_t key)
{
	/*
	 * The hash index is the computed prime times the key modulo
	 * the hash size, as documented in "Introduction to Algorithms"
	 * (Cormen, Leiserson, Rivest).
	 */
	if (inaddr_nhash > 1)
		return ((key * inaddr_hashp) % inaddr_nhash);
	else
		return (0);
}