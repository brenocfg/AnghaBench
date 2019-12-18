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
struct alloc_string {char* s; struct alloc_string* next; } ;

/* Variables and functions */
 struct alloc_string* strings ; 
 void* xmalloc (int) ; 

__attribute__((used)) static char *
get_string (int len)
{
  struct alloc_string *as;

  as = xmalloc (sizeof *as);
  as->s = xmalloc (len);

  as->next = strings;
  strings = as;

  return as->s;
}