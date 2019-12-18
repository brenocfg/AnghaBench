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
struct demangle_component {int dummy; } ;
struct d_standard_sub_info {char code; char const* set_last_name; int set_last_name_len; char* full_expansion; int full_len; char* simple_expansion; int simple_len; } ;
struct d_info {int next_sub; int options; int expansion; struct demangle_component* last_name; struct demangle_component** subs; int /*<<< orphan*/  did_subs; } ;

/* Variables and functions */
 int DMGL_VERBOSE ; 
 scalar_t__ IS_DIGIT (char) ; 
 scalar_t__ IS_UPPER (char) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 struct demangle_component* d_make_sub (struct d_info*,char const*,int) ; 
 char d_next_char (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 
 struct d_standard_sub_info* standard_subs ; 

__attribute__((used)) static struct demangle_component *
d_substitution (struct d_info *di, int prefix)
{
  char c;

  if (! d_check_char (di, 'S'))
    return NULL;

  c = d_next_char (di);
  if (c == '_' || IS_DIGIT (c) || IS_UPPER (c))
    {
      int id;

      id = 0;
      if (c != '_')
	{
	  do
	    {
	      if (IS_DIGIT (c))
		id = id * 36 + c - '0';
	      else if (IS_UPPER (c))
		id = id * 36 + c - 'A' + 10;
	      else
		return NULL;
	      if (id < 0)
		return NULL;
	      c = d_next_char (di);
	    }
	  while (c != '_');

	  ++id;
	}

      if (id >= di->next_sub)
	return NULL;

      ++di->did_subs;

      return di->subs[id];
    }
  else
    {
      int verbose;
      const struct d_standard_sub_info *p;
      const struct d_standard_sub_info *pend;

      verbose = (di->options & DMGL_VERBOSE) != 0;
      if (! verbose && prefix)
	{
	  char peek;

	  peek = d_peek_char (di);
	  if (peek == 'C' || peek == 'D')
	    verbose = 1;
	}

      pend = (&standard_subs[0]
	      + sizeof standard_subs / sizeof standard_subs[0]);
      for (p = &standard_subs[0]; p < pend; ++p)
	{
	  if (c == p->code)
	    {
	      const char *s;
	      int len;

	      if (p->set_last_name != NULL)
		di->last_name = d_make_sub (di, p->set_last_name,
					    p->set_last_name_len);
	      if (verbose)
		{
		  s = p->full_expansion;
		  len = p->full_len;
		}
	      else
		{
		  s = p->simple_expansion;
		  len = p->simple_len;
		}
	      di->expansion += len;
	      return d_make_sub (di, s, len);
	    }
	}

      return NULL;
    }
}