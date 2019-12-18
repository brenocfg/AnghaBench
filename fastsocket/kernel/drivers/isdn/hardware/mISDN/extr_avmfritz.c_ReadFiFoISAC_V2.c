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
typedef  int u8 ;
struct fritzcard {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ AVM_ISACX_DATA ; 
 scalar_t__ AVM_ISACX_INDEX ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void
ReadFiFoISAC_V2(void *p, u8 off, u8 *data, int size)
{
	struct fritzcard *fc = p;
	int i;

	outl(off, fc->addr + AVM_ISACX_INDEX);
	for (i = 0; i < size; i++)
		data[i] = 0xff & inl(fc->addr + AVM_ISACX_DATA);
}