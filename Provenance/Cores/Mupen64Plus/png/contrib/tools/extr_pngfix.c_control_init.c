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
struct global {int dummy; } ;
struct control {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocate ; 
 int file_init (int /*<<< orphan*/ *,struct global*,char const*,char const*,struct control*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
control_init(struct control *control, struct global *global,
   const char *file_name, const char *out_name)
   /* This wraps file_init(&control::file) and simply returns the result from
    * file_init.
    */
{
   return file_init(&control->file, global, file_name, out_name, control,
      allocate);
}