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
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static void rs_poly_copy(unsigned char *_p,const unsigned char *_q,int _dp1){
  memcpy(_p,_q,_dp1*sizeof(*_p));
}