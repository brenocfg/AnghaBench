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
struct TYPE_2__ {scalar_t__ viHeight; } ;

/* Variables and functions */
 TYPE_1__ gx_mode ; 
 scalar_t__ max_height ; 

__attribute__((used)) static bool gx_isValidYOrigin(int origin)
{
	if(origin < 0 || gx_mode.viHeight + origin > max_height)
	   return false;
	return true;
}