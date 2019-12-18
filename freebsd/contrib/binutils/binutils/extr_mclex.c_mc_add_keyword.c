#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wind_language_t ;
typedef  int /*<<< orphan*/  unichar ;
typedef  void* rc_uint_type ;
struct TYPE_4__ {size_t len; char const* group_name; int rid; struct TYPE_4__* next; int /*<<< orphan*/  lang_info; int /*<<< orphan*/ * sval; void* nval; int /*<<< orphan*/ * usz; } ;
typedef  TYPE_1__ mc_keyword ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 TYPE_1__* keyword_top ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/ * unichar_dup (int /*<<< orphan*/ *) ; 
 size_t unichar_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wind_find_language_by_id (unsigned int) ; 
 TYPE_1__* xmalloc (int) ; 

void
mc_add_keyword (unichar *usz, int rid, const char *grp, rc_uint_type nv, unichar *sv)
{
  mc_keyword *p, *c, *n;
  size_t len = unichar_len (usz);

  c = keyword_top;
  p = NULL;
  while (c != NULL)
    {
      if (c->len > len)
	break;
      if (c->len == len)
	{
	  int e = memcmp (usz, c->usz, len * sizeof (unichar));

	  if (e < 0)
	    break;
	  if (! e)
	    {
	      if (! strcmp (grp, "keyword") || strcmp (c->group_name, grp) != 0)
		fatal (_("Duplicate symbol entered into keyword list."));
	      c->rid = rid;
	      c->nval = nv;
	      c->sval = (!sv ? NULL : unichar_dup (sv));
	      if (! strcmp (grp, "language"))
		{
		  const wind_language_t *lag = wind_find_language_by_id ((unsigned) nv);

		  if (lag == NULL)
		    fatal ("Language ident 0x%lx is not resolvable.\n", (long) nv);
		  memcpy (&c->lang_info, lag, sizeof (*lag));
		}
	      return;
	    }
	}
      c = (p = c)->next;
    }
  n = xmalloc (sizeof (mc_keyword));
  n->next = c;
  n->len = len;
  n->group_name = grp;
  n->usz = usz;
  n->rid = rid;
  n->nval = nv;
  n->sval = (!sv ? NULL : unichar_dup (sv));
  if (! strcmp (grp, "language"))
    {
      const wind_language_t *lag = wind_find_language_by_id ((unsigned) nv);
      if (lag == NULL)
	fatal ("Language ident 0x%lx is not resolvable.\n", (long) nv);
      memcpy (&n->lang_info, lag, sizeof (*lag));
    }
  if (! p)
    keyword_top = n;
  else
    p->next = n;
}