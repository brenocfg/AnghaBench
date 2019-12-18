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
init_intraclass_conv_libfuncs (convert_optab tab, const char *opname,
			       enum mode_class class, bool widening)
{
  enum machine_mode first_mode = GET_CLASS_NARROWEST_MODE (class);
  size_t opname_len = strlen (opname);
  size_t max_mname_len = 0;

  enum machine_mode nmode, wmode;
  const char *nname, *wname;
  const char *q;
  char *libfunc_name, *suffix;
  char *p;

  for (nmode = first_mode; nmode != VOIDmode;
       nmode = GET_MODE_WIDER_MODE (nmode))
    max_mname_len = MAX (max_mname_len, strlen (GET_MODE_NAME (nmode)));

  libfunc_name = alloca (2 + opname_len + 2*max_mname_len + 1 + 1);
  libfunc_name[0] = '_';
  libfunc_name[1] = '_';
  memcpy (&libfunc_name[2], opname, opname_len);
  suffix = libfunc_name + opname_len + 2;

  for (nmode = first_mode; nmode != VOIDmode;
       nmode = GET_MODE_WIDER_MODE (nmode))
    for (wmode = GET_MODE_WIDER_MODE (nmode); wmode != VOIDmode;
	 wmode = GET_MODE_WIDER_MODE (wmode))
      {
	nname = GET_MODE_NAME (nmode);
	wname = GET_MODE_NAME (wmode);

	p = suffix;
	for (q = widening ? nname : wname; *q; p++, q++)
	  *p = TOLOWER (*q);
	for (q = widening ? wname : nname; *q; p++, q++)
	  *p = TOLOWER (*q);

	*p++ = '2';
	*p = '\0';

	tab->handlers[widening ? wmode : nmode]
	             [widening ? nmode : wmode].libfunc
	  = init_one_libfunc (ggc_alloc_string (libfunc_name,
						p - libfunc_name));
      }
}