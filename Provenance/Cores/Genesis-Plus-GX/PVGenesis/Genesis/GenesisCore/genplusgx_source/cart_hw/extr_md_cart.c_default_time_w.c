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
typedef  int uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  mapper_64k_multi_w (int) ; 
 int /*<<< orphan*/  mapper_sega_w (int) ; 

__attribute__((used)) static void default_time_w(uint32 address, uint32 data)
{
  if (address < 0xa13040)
  {
    /* unlicensed cartridges mapper (default) */
    mapper_64k_multi_w(address);
    return;
  }

  /* official cartridges mapper (default) */
  mapper_sega_w(data);
}