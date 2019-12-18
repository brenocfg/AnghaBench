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
struct global {scalar_t__ verbose; } ;
struct control {int dummy; } ;

/* Variables and functions */
 int control_end (struct control*) ; 
 int control_init (struct control*,struct global*,char const*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int read_png (struct control*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
one_file(struct global *global, const char *file_name, const char *out_name)
{
   int rc;
   struct control control;

   if (global->verbose)
      fprintf(stderr, "FILE %s -> %s\n", file_name,
         out_name ? out_name : "<none>");

   /* Although control_init can return a failure code the structure is always
    * initialized, so control_end can be used to accumulate any status codes.
    */
   rc = control_init(&control, global, file_name, out_name);

   if (rc == 0)
      rc = read_png(&control);

   rc |= control_end(&control);

   return rc;
}