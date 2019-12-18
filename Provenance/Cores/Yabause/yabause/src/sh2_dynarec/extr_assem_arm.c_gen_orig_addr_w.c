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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int,int,int) ; 
 int /*<<< orphan*/ * regname ; 

int gen_orig_addr_w(int ar, int map) {
  if(map>=0) {
    assem_debug("sub %s,%s,%s lsl #2\n",regname[ar],regname[ar],regname[map]);
    output_w32(0xe0400100|rd_rn_rm(ar,ar,map));
  }
}