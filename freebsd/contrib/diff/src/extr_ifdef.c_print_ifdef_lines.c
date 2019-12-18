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
struct group {size_t from; size_t upto; struct file_data* file; } ;
struct file_data {char** linbuf; } ;
typedef  size_t lin ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* do_printf_spec (int /*<<< orphan*/ *,char const*,struct file_data const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_tabs ; 
 int /*<<< orphan*/  fwrite (char const* const,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_1_line (char const* const,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_ifdef_lines (register FILE *out, char const *format,
		   struct group const *group)
{
  struct file_data const *file = group->file;
  char const * const *linbuf = file->linbuf;
  lin from = group->from, upto = group->upto;

  if (!out)
    return;

  /* If possible, use a single fwrite; it's faster.  */
  if (!expand_tabs && format[0] == '%')
    {
      if (format[1] == 'l' && format[2] == '\n' && !format[3] && from < upto)
	{
	  fwrite (linbuf[from], sizeof (char),
		  linbuf[upto] + (linbuf[upto][-1] != '\n') -  linbuf[from],
		  out);
	  return;
	}
      if (format[1] == 'L' && !format[2])
	{
	  fwrite (linbuf[from], sizeof (char),
		  linbuf[upto] -  linbuf[from], out);
	  return;
	}
    }

  for (;  from < upto;  from++)
    {
      register char c;
      register char const *f = format;

      while ((c = *f++) != 0)
	{
	  char const *f1 = f;
	  if (c == '%')
	    switch ((c = *f++))
	      {
	      case '%':
		break;

	      case 'l':
		output_1_line (linbuf[from],
			       (linbuf[from + 1]
				- (linbuf[from + 1][-1] == '\n')),
			       0, 0);
		continue;

	      case 'L':
		output_1_line (linbuf[from], linbuf[from + 1], 0, 0);
		continue;

	      default:
		f = do_printf_spec (out, f - 2, file, from, 0);
		if (f)
		  continue;
		c = '%';
		f = f1;
		break;
	      }

	  putc (c, out);
	}
    }
}