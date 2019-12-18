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
typedef  int u16 ;
struct bf54x_kpad {int dummy; } ;

/* Variables and functions */
 int KPAD_PRESSED ; 
 int bfin_read_KPAD_STAT () ; 

__attribute__((used)) static inline u16 bfin_kpad_get_keypressed(struct bf54x_kpad *bf54x_kpad)
{
	return (bfin_read_KPAD_STAT() & KPAD_PRESSED);
}