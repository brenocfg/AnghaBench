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
typedef  int /*<<< orphan*/  UInt8 ;
typedef  int /*<<< orphan*/  UInt32 ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  OSTestAndSetClear (int /*<<< orphan*/ ,int,int /*<<< orphan*/  volatile*) ; 

Boolean OSTestAndSet(UInt32 bit, volatile UInt8 * startAddress)
{
	return OSTestAndSetClear(bit, true, startAddress);
}