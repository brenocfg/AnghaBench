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
typedef  int /*<<< orphan*/  SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/ * MSH2 ; 
 int /*<<< orphan*/ * SSH2 ; 
 scalar_t__ master_cc ; 
 scalar_t__ slave_cc ; 
 void* slave_ip ; 

void SH2DynarecReset(SH2_struct *context) {

  //printf("SH2DynarecReset\n");
  if(context==MSH2) master_cc=0;
  if(context==SSH2) { slave_ip=(void*)0; slave_cc=0; }
}