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
 int bsd_init (void*,unsigned char*,int,int,int,int) ; 

__attribute__((used)) static int bsd_decomp_init (void *state, unsigned char *options,
			    int opt_len, int unit, int opthdr, int mru,
			    int debug)
  {
    return bsd_init (state, options, opt_len, unit, debug, 1);
  }