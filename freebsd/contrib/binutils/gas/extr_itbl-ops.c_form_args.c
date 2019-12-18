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
struct itbl_field {int type; struct itbl_field* next; } ;
struct itbl_entry {struct itbl_field* fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct itbl_entry*) ; 
#define  e_addr 132 
#define  e_creg 131 
#define  e_dreg 130 
#define  e_greg 129 
#define  e_immed 128 

__attribute__((used)) static char *
form_args (struct itbl_entry *e)
{
  static char s[31];
  char c = 0, *p = s;
  struct itbl_field *f;

  ASSERT (e);
  for (f = e->fields; f; f = f->next)
    {
      switch (f->type)
	{
	case e_dreg:
	  c = 'd';
	  break;
	case e_creg:
	  c = 't';
	  break;
	case e_greg:
	  c = 's';
	  break;
	case e_immed:
	  c = 'i';
	  break;
	case e_addr:
	  c = 'a';
	  break;
	default:
	  c = 0;		/* ignore; unknown field type */
	}
      if (c)
	{
	  if (p != s)
	    *p++ = ',';
	  *p++ = c;
	}
    }
  *p = 0;
  return s;
}