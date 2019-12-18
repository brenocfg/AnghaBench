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
struct cpp_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  cpp_reader ;
typedef  int /*<<< orphan*/  cpp_dir ;

/* Variables and functions */
 struct cpp_buffer* cpp_get_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cpp_get_dir (scalar_t__) ; 
 scalar_t__ cpp_get_file (struct cpp_buffer*) ; 
 scalar_t__ cpp_get_path (scalar_t__) ; 
 struct cpp_buffer* cpp_get_prev (struct cpp_buffer*) ; 
 char* find_subframework_file (char const*,scalar_t__) ; 

__attribute__((used)) static const char*
find_subframework_header (cpp_reader *pfile, const char *header, cpp_dir **dirp)
{
  const char *fname = header;
  struct cpp_buffer *b;
  const char *n;

  for (b = cpp_get_buffer (pfile);
       b && cpp_get_file (b) && cpp_get_path (cpp_get_file (b));
       b = cpp_get_prev (b))
    {
      n = find_subframework_file (fname, cpp_get_path (cpp_get_file (b)));
      if (n)
	{
	  /* Logically, the place where we found the subframework is
	     the place where we found the Framework that contains the
	     subframework.  This is useful for tracking wether or not
	     we are in a system header.  */
	  *dirp = cpp_get_dir (cpp_get_file (b));
	  return n;
	}
    }

  return 0;
}