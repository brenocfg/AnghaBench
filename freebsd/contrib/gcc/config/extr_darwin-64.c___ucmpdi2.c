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
typedef  int word_type ;
typedef  scalar_t__ uDI ;

/* Variables and functions */

word_type __ucmpdi2 (uDI x, uDI y) { return x < y ? 0 : x == y ? 1 : 2; }