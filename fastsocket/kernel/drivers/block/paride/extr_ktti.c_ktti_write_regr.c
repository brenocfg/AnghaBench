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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int* cont_map ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void  ktti_write_regr( PIA *pi, int cont, int regr, int val)

{	int r;

	r = regr + cont_map[cont];

	w0(r); w2(0xb); w2(0xa); w2(3); w2(6); 
	w0(val); w2(3); w0(0); w2(6); w2(0xb);
}