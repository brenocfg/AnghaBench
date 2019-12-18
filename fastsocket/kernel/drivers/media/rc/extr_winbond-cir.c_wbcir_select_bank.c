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
struct wbcir_data {scalar_t__ sbase; } ;
typedef  enum wbcir_bank { ____Placeholder_wbcir_bank } wbcir_bank ;

/* Variables and functions */
 scalar_t__ WBCIR_REG_SP3_BSR ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static inline void
wbcir_select_bank(struct wbcir_data *data, enum wbcir_bank bank)
{
	outb(bank, data->sbase + WBCIR_REG_SP3_BSR);
}