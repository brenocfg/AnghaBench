#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_1__* global; } ;
struct TYPE_2__ {scalar_t__ errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  emit_error (struct file*,int,char const*) ; 

__attribute__((used)) static void
log_error(struct file *file, int code, const char *what)
   /* Like emit_error but checks the global 'errors' flag */
{
   if (file->global->errors)
      emit_error(file, code, what);
}