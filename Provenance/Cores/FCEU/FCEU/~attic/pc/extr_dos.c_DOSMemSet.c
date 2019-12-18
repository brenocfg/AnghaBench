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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  _dos_ds ; 
 int /*<<< orphan*/  _farnspokeb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _farsetsel (int /*<<< orphan*/ ) ; 

void DOSMemSet(uint32 A, uint8 V, uint32 count)
{
 uint32 x;

 _farsetsel(_dos_ds);
 for(x=0;x<count;x++)
  _farnspokeb(A+x,V);
}