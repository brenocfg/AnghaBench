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
typedef  int /*<<< orphan*/  pss_confdata ;

/* Variables and functions */
 int /*<<< orphan*/  pss_write (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void set_treble(pss_confdata *devc, int level)
{	
	int vol = (((0xfd - 0xf0) * level)/100L) + 0xf0;
	pss_write(devc, 0x0010);
	pss_write(devc, vol | 0x0300);
}