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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  ICEDS (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEX ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void snd_ice1712_ds_write(struct snd_ice1712 *ice, u8 channel, u8 addr, u32 data)
{
	outb((channel << 4) | addr, ICEDS(ice, INDEX));
	outl(data, ICEDS(ice, DATA));
}