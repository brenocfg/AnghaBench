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
 scalar_t__ FF_QP2LAMBDA ; 
 int QROOT ; 
 int log2 (int) ; 
 int lrint (int) ; 

__attribute__((used)) static int qscale2qlog(int qscale){
    return lrint(QROOT*log2(qscale / (float)FF_QP2LAMBDA))
           + 61*QROOT/8; ///< 64 > 60
}