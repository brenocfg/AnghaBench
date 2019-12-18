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
struct TYPE_2__ {short* b; short* s; } ;
typedef  TYPE_1__ conv ;

/* Variables and functions */

short intel_short(short l)
{
	conv t;

	t.b[0] = l & 0xff; l >>= 8;
	t.b[1] = l & 0xff; l >>= 8;
	return t.s[0];
}