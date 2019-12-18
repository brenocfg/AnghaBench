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
struct TYPE_3__ {int* pi; } ;
typedef  TYPE_1__ yxml_t ;
typedef  int /*<<< orphan*/  yxml_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  YXML_ESYN ; 
 int /*<<< orphan*/  YXML_PISTART ; 

__attribute__((used)) static inline yxml_ret_t yxml_pinameend(yxml_t *x, unsigned ch) {
	return (x->pi[0]|32) == 'x' && (x->pi[1]|32) == 'm' && (x->pi[2]|32) == 'l' && !x->pi[3] ? YXML_ESYN : YXML_PISTART;
}