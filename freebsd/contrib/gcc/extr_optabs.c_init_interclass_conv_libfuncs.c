#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum mode_class { ____Placeholder_mode_class } mode_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  TYPE_2__* convert_optab ;
struct TYPE_5__ {TYPE_1__** handlers; } ;
struct TYPE_4__ {int /*<<< orphan*/  libfunc; } ;

/* Variables and functions */
 int GET_CLASS_NARROWEST_MODE (int) ; 
 char const* GET_MODE_NAME (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 size_t MAX (size_t,size_t) ; 
 char TOLOWER (char const) ; 
 int VOIDmode ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  ggc_alloc_string (char*,int) ; 
 int /*<<< orphan*/  init_one_libfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
init_interclass_conv_libfuncs (convert_optab tab, const char *opname,
			       enum mode_class from_class,
			       enum mode_class to_class)
{
  enum machine_mode first_from_mode = GET_CLASS_NARROWEST_MODE (from_class);
  enum machine_mode first_to_mode = GET_CLASS_NARROWEST_MODE (to_class);
  size_t opname_len = strlen (opname);
  size_t max_mname_len = 0;

  enum machine_mode fmode, tmode;
  const char *fname, *tname;
  const char *q;
  char *libfunc_name, *suffix;
  char *p;

  for (fmode = first_from_mode;
       fmode != VOIDmode;
       fmode = GET_MODE_WIDER_MODE (fmode))
    max_mname_len = MAX (max_mname_len, strlen (GET_MODE_NAME (fmode)));

  for (tmode = first_to_mode;
       tmode != VOIDmode;
       tmode = GET_MODE_WIDER_MODE (tmode))
    max_mname_len = MAX (max_mname_len, strlen (GET_MODE_NAME (tmode)));

  libfunc_name = alloca (2 + opname_len + 2*max_mname_len + 1 + 1);
  libfunc_name[0] = '_';
  libfunc_name[1] = '_';
  memcpy (&libfunc_name[2], opname, opname_len);
  suffix = libfunc_name + opname_len + 2;

  for (fmode = first_from_mode; fmode != VOIDmode;
       fmode = GET_MODE_WIDER_MODE (fmode))
    for (tmode = first_to_mode; tmode != VOIDmode;
	 tmode = GET_MODE_WIDER_MODE (tmode))
      {
	fname = GET_MODE_NAME (fmode);
	tname = GET_MODE_NAME (tmode);

	p = suffix;
	for (q = fname; *q; p++, q++)
	  *p = TOLOWER (*q);
	for (q = tname; *q; p++, q++)
	  *p = TOLOWER (*q);

	*p = '\0';

	tab->handlers[tmode][fmode].libfunc
	  = init_one_libfunc (ggc_alloc_string (libfunc_name,
						p - libfunc_name));
      }
}