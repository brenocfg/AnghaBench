#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int bt_byteorder; } ;
typedef  TYPE_1__ Elftc_Bfd_Target ;

/* Variables and functions */

unsigned int
elftc_bfd_target_byteorder(Elftc_Bfd_Target *tgt)
{

	return (tgt->bt_byteorder);
}