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
struct p9_fcall {scalar_t__ size; scalar_t__ offset; } ;

/* Variables and functions */

void p9pdu_reset(struct p9_fcall *pdu)
{
	pdu->offset = 0;
	pdu->size = 0;
}