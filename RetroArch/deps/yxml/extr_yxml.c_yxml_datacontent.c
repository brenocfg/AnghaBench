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
struct TYPE_3__ {scalar_t__* data; } ;
typedef  TYPE_1__ yxml_t ;
typedef  int /*<<< orphan*/  yxml_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  YXML_CONTENT ; 
 int /*<<< orphan*/  yxml_setchar (scalar_t__*,unsigned int) ; 

__attribute__((used)) static inline yxml_ret_t yxml_datacontent(yxml_t *x, unsigned ch) {
	yxml_setchar(x->data, ch);
	x->data[1] = 0;
	return YXML_CONTENT;
}