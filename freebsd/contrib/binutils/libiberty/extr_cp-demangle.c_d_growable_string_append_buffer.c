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
struct d_growable_string {size_t len; size_t alc; char* buf; scalar_t__ allocation_failure; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_growable_string_resize (struct d_growable_string*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static inline void
d_growable_string_append_buffer (struct d_growable_string *dgs,
                                 const char *s, size_t l)
{
  size_t need;

  need = dgs->len + l + 1;
  if (need > dgs->alc)
    d_growable_string_resize (dgs, need);

  if (dgs->allocation_failure)
    return;

  memcpy (dgs->buf + dgs->len, s, l);
  dgs->buf[dgs->len + l] = '\0';
  dgs->len += l;
}