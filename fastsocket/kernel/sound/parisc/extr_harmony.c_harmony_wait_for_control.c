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
 int /*<<< orphan*/  HARMONY_CNTL ; 
 int HARMONY_CNTL_C ; 
 int harmony_read (struct snd_harmony*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
harmony_wait_for_control(struct snd_harmony *h)
{
	while (harmony_read(h, HARMONY_CNTL) & HARMONY_CNTL_C) ;
}