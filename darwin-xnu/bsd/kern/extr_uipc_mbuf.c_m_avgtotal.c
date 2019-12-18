#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t mbuf_class_t ;
struct TYPE_2__ {int /*<<< orphan*/  mtbl_avgtotal; } ;

/* Variables and functions */
 TYPE_1__* mbuf_table ; 

__attribute__((used)) static uint32_t
m_avgtotal(mbuf_class_t c)
{
	return (mbuf_table[c].mtbl_avgtotal);
}