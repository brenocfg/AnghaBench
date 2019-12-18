#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct hash_control {int dummy; } ;
struct TYPE_12__ {char* ptr; scalar_t__ len; } ;
typedef  TYPE_1__ sb ;
struct TYPE_13__ {TYPE_1__ def; TYPE_1__ actual; } ;
typedef  TYPE_2__ formal_entry ;

/* Variables and functions */
 int get_apost_token (int,TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ hash_find (struct hash_control*,int /*<<< orphan*/ ) ; 
 scalar_t__ macro_strip_at ; 
 int /*<<< orphan*/  sb_add_char (TYPE_1__*,char) ; 
 int /*<<< orphan*/  sb_add_sb (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sb_terminate (TYPE_1__*) ; 

__attribute__((used)) static int
sub_actual (int start, sb *in, sb *t, struct hash_control *formal_hash,
	    int kind, sb *out, int copyifnotthere)
{
  int src;
  formal_entry *ptr;

  src = get_apost_token (start, in, t, kind);
  /* See if it's in the macro's hash table, unless this is
     macro_strip_at and kind is '@' and the token did not end in '@'.  */
  if (macro_strip_at
      && kind == '@'
      && (src == start || in->ptr[src - 1] != '@'))
    ptr = NULL;
  else
    ptr = (formal_entry *) hash_find (formal_hash, sb_terminate (t));
  if (ptr)
    {
      if (ptr->actual.len)
	{
	  sb_add_sb (out, &ptr->actual);
	}
      else
	{
	  sb_add_sb (out, &ptr->def);
	}
    }
  else if (kind == '&')
    {
      /* Doing this permits people to use & in macro bodies.  */
      sb_add_char (out, '&');
      sb_add_sb (out, t);
    }
  else if (copyifnotthere)
    {
      sb_add_sb (out, t);
    }
  else
    {
      sb_add_char (out, '\\');
      sb_add_sb (out, t);
    }
  return src;
}