#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int pending_int_irq; unsigned int pending_int_vector; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int SH2_REG_SIZE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,TYPE_1__ const*,int) ; 

void sh2_pack(const SH2 *sh2, unsigned char *buff)
{
	unsigned int *p;

	memcpy(buff, sh2, SH2_REG_SIZE);
	p = (void *)(buff + SH2_REG_SIZE);

	p[0] = sh2->pending_int_irq;
	p[1] = sh2->pending_int_vector;
}