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
struct prom_args {int dummy; } ;

/* Variables and functions */
 int stub1 (struct prom_args*) ; 

__attribute__((used)) static inline int enter_prom(struct prom_args *args, unsigned long entry)
{
	return ((int (*)(struct prom_args *))entry)(args);
}