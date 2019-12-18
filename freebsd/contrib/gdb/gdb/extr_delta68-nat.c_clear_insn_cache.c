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
 int /*<<< orphan*/  MCT_TEXT ; 
 int /*<<< orphan*/  memctl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

clear_insn_cache (void)
{
#ifdef MCT_TEXT			/* in sys/signal.h on sysV68 R3V7.1 */
  memctl (0, 4096, MCT_TEXT);
#endif
}