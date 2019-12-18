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
struct tty_struct {size_t index; } ;
struct nozomi {int dummy; } ;

/* Variables and functions */
 size_t MAX_PORT ; 
 struct nozomi** ndevs ; 

__attribute__((used)) static inline struct nozomi *get_dc_by_tty(const struct tty_struct *tty)
{
	return tty ? ndevs[tty->index / MAX_PORT] : NULL;
}