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
 int PORT_EN ; 
 int bfin_read_PPI_CONTROL () ; 
 int /*<<< orphan*/  bfin_write_PPI_CONTROL (int) ; 

__attribute__((used)) static inline void bfin_t350mcqb_enable_ppi(void)
{
	bfin_write_PPI_CONTROL(bfin_read_PPI_CONTROL() | PORT_EN);
}