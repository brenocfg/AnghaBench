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
typedef  int /*<<< orphan*/  opj_tcd_tilecomp_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwt_decode_1 ; 
 int /*<<< orphan*/  dwt_decode_tile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void dwt_decode(opj_tcd_tilecomp_t* tilec, int numres) {
	dwt_decode_tile(tilec, numres, &dwt_decode_1);
}