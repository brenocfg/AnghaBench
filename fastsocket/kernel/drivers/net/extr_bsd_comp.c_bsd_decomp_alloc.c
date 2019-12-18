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
 void* bsd_alloc (unsigned char*,int,int) ; 

__attribute__((used)) static void *bsd_decomp_alloc (unsigned char *options, int opt_len)
  {
    return bsd_alloc (options, opt_len, 1);
  }