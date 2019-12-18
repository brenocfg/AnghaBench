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
struct confset {size_t cs_n; struct conf* cs_c; } ;
struct conf {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct conf *
confset_get(struct confset *cs)
{
	return &cs->cs_c[cs->cs_n];
}