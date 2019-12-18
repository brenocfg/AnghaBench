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
 int bit (int) ; 
 int /*<<< orphan*/  ks0108_writedata (int) ; 
 int min (unsigned char,unsigned char) ; 

void ks0108_address(unsigned char address)
{
	ks0108_writedata(min(address,(unsigned char)63) | bit(6));
}