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
 int JQS_wHead ; 
 int JQS_wSize ; 
 int JQS_wStart ; 
 int JQS_wTail ; 
 scalar_t__ PCTODSP_BASED (int) ; 
 scalar_t__ PCTODSP_OFFSET (int) ; 
 int /*<<< orphan*/  writew (scalar_t__,void*) ; 

void snd_msnd_init_queue(void *base, int start, int size)
{
	writew(PCTODSP_BASED(start), base + JQS_wStart);
	writew(PCTODSP_OFFSET(size) - 1, base + JQS_wSize);
	writew(0, base + JQS_wHead);
	writew(0, base + JQS_wTail);
}