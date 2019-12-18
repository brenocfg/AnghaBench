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
typedef  int /*<<< orphan*/  ieee754sp ;

/* Variables and functions */
 int IEEE754_CGT ; 
 int IEEE754_CLT ; 
 int IEEE754_CUN ; 
 int ieee754sp_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ieee754sp_ne(ieee754sp x, ieee754sp y)
{
	return ieee754sp_cmp(x, y,
			     IEEE754_CLT | IEEE754_CGT | IEEE754_CUN, 0);
}