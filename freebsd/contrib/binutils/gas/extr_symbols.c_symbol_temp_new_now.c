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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  frag_now_fix () ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/ * symbol_temp_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

symbolS *
symbol_temp_new_now (void)
{
  return symbol_temp_new (now_seg, frag_now_fix (), frag_now);
}