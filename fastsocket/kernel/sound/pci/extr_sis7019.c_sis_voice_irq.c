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
typedef  int u32 ;
struct voice {int dummy; } ;

/* Variables and functions */
 int __ffs (int) ; 
 int /*<<< orphan*/  sis_update_voice (struct voice*) ; 

__attribute__((used)) static void sis_voice_irq(u32 status, struct voice *voice)
{
	int bit;

	while (status) {
		bit = __ffs(status);
		status >>= bit + 1;
		voice += bit;
		sis_update_voice(voice);
		voice++;
	}
}