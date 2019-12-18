#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* high; void* low; } ;
struct TYPE_6__ {TYPE_1__ bytes; } ;
struct TYPE_7__ {scalar_t__ DSPbase; TYPE_2__ hsr; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 void* inb_p (scalar_t__) ; 

__attribute__((used)) static inline void ixj_read_HSR(IXJ *j)
{
	j->hsr.bytes.low = inb_p(j->DSPbase + 8);
	j->hsr.bytes.high = inb_p(j->DSPbase + 9);
}