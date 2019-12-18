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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  shared_obj ; 
 int /*<<< orphan*/  write_c_file_glob (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  write_c_file_stat (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
write_c_file (FILE *stream, const char *name)
{
  fprintf (stream, "#ifdef __cplusplus\nextern \"C\" {\n#endif\n");
#ifndef LD_INIT_SWITCH
  if (! shared_obj)
    write_c_file_glob (stream, name);
  else
#endif
    write_c_file_stat (stream, name);
  fprintf (stream, "#ifdef __cplusplus\n}\n#endif\n");
}