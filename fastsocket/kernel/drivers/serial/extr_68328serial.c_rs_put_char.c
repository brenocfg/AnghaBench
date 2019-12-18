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
 int UTX ; 
 char UTX_TXDATA ; 
 int UTX_TX_AVAIL ; 
 int /*<<< orphan*/  local_irq_restore (int) ; 
 int /*<<< orphan*/  local_irq_save (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rs_put_char(char ch)
{
        int flags, loops = 0;

        local_irq_save(flags);

	while (!(UTX & UTX_TX_AVAIL) && (loops < 1000)) {
        	loops++;
        	udelay(5);
        }

	UTX_TXDATA = ch;
        udelay(5);
        local_irq_restore(flags);
        return 1;
}