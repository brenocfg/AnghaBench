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
struct dwarf_fde {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cie (struct dwarf_fde const*) ; 
 int get_cie_encoding (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
get_fde_encoding (const struct dwarf_fde *f)
{
  return get_cie_encoding (get_cie (f));
}