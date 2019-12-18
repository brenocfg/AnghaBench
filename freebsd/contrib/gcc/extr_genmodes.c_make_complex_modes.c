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
struct mode_data {int precision; char* name; char* line; struct mode_data* component; int /*<<< orphan*/  file; struct mode_data* next; } ;
typedef  enum mode_class { ____Placeholder_mode_class } mode_class ;

/* Variables and functions */
 int MODE_FLOAT ; 
 int MODE_RANDOM ; 
 int complex_class (int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct mode_data** modes ; 
 struct mode_data* new_mode (int,int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
make_complex_modes (enum mode_class cl,
		    const char *file, unsigned int line)
{
  struct mode_data *m;
  struct mode_data *c;
  char buf[8];
  enum mode_class cclass = complex_class (cl);

  if (cclass == MODE_RANDOM)
    return;

  for (m = modes[cl]; m; m = m->next)
    {
      /* Skip BImode.  FIXME: BImode probably shouldn't be MODE_INT.  */
      if (m->precision == 1)
	continue;

      if (strlen (m->name) >= sizeof buf)
	{
	  error ("%s:%d:mode name \"%s\" is too long",
		 m->file, m->line, m->name);
	  continue;
	}

      /* Float complex modes are named SCmode, etc.
	 Int complex modes are named CSImode, etc.
         This inconsistency should be eliminated.  */
      if (cl == MODE_FLOAT)
	{
	  char *p, *q = 0;
	  strncpy (buf, m->name, sizeof buf);
	  p = strchr (buf, 'F');
	  if (p == 0)
	    q = strchr (buf, 'D');
	  if (p == 0 && q == 0)
	    {
	      error ("%s:%d: float mode \"%s\" has no 'F' or 'D'",
		     m->file, m->line, m->name);
	      continue;
	    }

	  if (p != 0)
	    *p = 'C';
	  else
	    snprintf (buf, sizeof buf, "C%s", m->name);
	}
      else
	snprintf (buf, sizeof buf, "C%s", m->name);

      c = new_mode (cclass, xstrdup (buf), file, line);
      c->component = m;
    }
}