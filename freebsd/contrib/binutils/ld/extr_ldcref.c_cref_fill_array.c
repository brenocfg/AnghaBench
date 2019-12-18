#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * string; } ;
struct cref_hash_entry {TYPE_1__ root; int /*<<< orphan*/ * demangled; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_demangle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  output_bfd ; 

__attribute__((used)) static bfd_boolean
cref_fill_array (struct cref_hash_entry *h, void *data)
{
  struct cref_hash_entry ***pph = data;

  ASSERT (h->demangled == NULL);
  h->demangled = bfd_demangle (output_bfd, h->root.string,
			       DMGL_ANSI | DMGL_PARAMS);
  if (h->demangled == NULL)
    h->demangled = h->root.string;

  **pph = h;

  ++*pph;

  return TRUE;
}