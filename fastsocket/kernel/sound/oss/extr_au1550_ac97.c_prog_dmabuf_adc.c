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
struct au1550_state {int /*<<< orphan*/  dma_adc; } ;

/* Variables and functions */
 int prog_dmabuf (struct au1550_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_adc (struct au1550_state*) ; 

__attribute__((used)) static int
prog_dmabuf_adc(struct au1550_state *s)
{
	stop_adc(s);
	return prog_dmabuf(s, &s->dma_adc);

}