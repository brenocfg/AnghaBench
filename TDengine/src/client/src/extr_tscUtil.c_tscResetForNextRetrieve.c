#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ numOfRows; scalar_t__ row; } ;
typedef  TYPE_1__ SSqlRes ;

/* Variables and functions */

void tscResetForNextRetrieve(SSqlRes* pRes) {
  pRes->row = 0;
  pRes->numOfRows = 0;
}