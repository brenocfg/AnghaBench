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
 int CARTRIDGE_ATRAX_SDX_128 ; 
 int CARTRIDGE_ATRAX_SDX_64 ; 
 int CARTRIDGE_SDX_128 ; 
 int CARTRIDGE_SDX_64 ; 

__attribute__((used)) static int CartIsPassthrough(int type)
{
	return type == CARTRIDGE_SDX_64 || type == CARTRIDGE_SDX_128 ||
	       type == CARTRIDGE_ATRAX_SDX_64 || type == CARTRIDGE_ATRAX_SDX_128;
}