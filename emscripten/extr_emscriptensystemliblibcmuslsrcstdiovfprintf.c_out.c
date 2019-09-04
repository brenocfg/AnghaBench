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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int F_ERR ; 
 int /*<<< orphan*/  __fwritex (void*,size_t,TYPE_1__*) ; 

__attribute__((used)) static void out(FILE *f, const char *s, size_t l)
{
	if (!(f->flags & F_ERR)) __fwritex((void *)s, l, f);
}