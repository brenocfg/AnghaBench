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
struct desc_struct {scalar_t__ a; scalar_t__ b; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_gdt_entry (struct desc_struct*,int,struct desc_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vmi_maybe_load_tls(struct desc_struct *gdt, int nr, struct desc_struct *new)
{
	if (gdt[nr].a != new->a || gdt[nr].b != new->b)
		write_gdt_entry(gdt, nr, new, 0);
}