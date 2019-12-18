#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int chan; int /*<<< orphan*/  substickY; } ;

/* Variables and functions */
 int PAD_CHAN0 ; 
 int PAD_CHAN3 ; 
 TYPE_1__* __pad_keys ; 

s8 PAD_SubStickY(int pad)
{
	if(pad<PAD_CHAN0 || pad>PAD_CHAN3 || __pad_keys[pad].chan==-1) return 0;
	return __pad_keys[pad].substickY;
}