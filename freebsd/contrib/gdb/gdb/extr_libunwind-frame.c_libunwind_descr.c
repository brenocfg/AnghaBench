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
struct libunwind_descr {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 struct libunwind_descr* gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libunwind_descr_handle ; 

__attribute__((used)) static struct libunwind_descr *
libunwind_descr (struct gdbarch *gdbarch)
{
  return gdbarch_data (gdbarch, libunwind_descr_handle);
}