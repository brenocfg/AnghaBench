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
struct snd_harmony {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARMONY_RESET ; 
 int /*<<< orphan*/  harmony_write (struct snd_harmony*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static inline void
harmony_reset(struct snd_harmony *h)
{
	harmony_write(h, HARMONY_RESET, 1);
	mdelay(50);
	harmony_write(h, HARMONY_RESET, 0);
}