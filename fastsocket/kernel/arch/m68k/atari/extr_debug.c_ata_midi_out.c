#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mid_ctrl; char mid_data; } ;

/* Variables and functions */
 int ACIA_TDRE ; 
 TYPE_1__ acia ; 
 int /*<<< orphan*/  barrier () ; 

__attribute__((used)) static inline void ata_midi_out(char c)
{
	while (!(acia.mid_ctrl & ACIA_TDRE))	/* wait for tx buf empty */
		barrier();
	acia.mid_data = c;
}