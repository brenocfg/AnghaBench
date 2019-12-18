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
 int /*<<< orphan*/  RDP_INFO ; 
 int /*<<< orphan*/  RDP_INFO_VECTOR_CATCH ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdp_catch_vectors (void)
{
  /*
     ** We want the target monitor to intercept the abort vectors
     ** i.e. stop the program if any of these are used.
   */
  send_rdp ("bww-SZ", RDP_INFO, RDP_INFO_VECTOR_CATCH,
  /*
     ** Specify a bitmask including
     **  the reset vector
     **  the undefined instruction vector
     **  the prefetch abort vector
     **  the data abort vector
     **  the address exception vector
   */
	    (1 << 0) | (1 << 1) | (1 << 3) | (1 << 4) | (1 << 5)
    );
}