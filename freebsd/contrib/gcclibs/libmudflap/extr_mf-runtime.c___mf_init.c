#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {uintptr_t low; } ;

/* Variables and functions */
 scalar_t__ LIKELY (int) ; 
 int /*<<< orphan*/  MINPTR ; 
 int /*<<< orphan*/  REG_RESERVED (TYPE_1__*) ; 
 int /*<<< orphan*/  __MF_TYPE_NOACCESS ; 
 int /*<<< orphan*/  __mf_describe_object (int /*<<< orphan*/ *) ; 
 TYPE_1__* __mf_lc_mask ; 
 TYPE_1__* __mf_lc_shift ; 
 TYPE_1__* __mf_lookup_cache ; 
 int /*<<< orphan*/  __mf_register (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  __mf_resolve_dynamics () ; 
 int /*<<< orphan*/  __mf_set_default_options () ; 
 int /*<<< orphan*/  __mf_set_state (int /*<<< orphan*/ ) ; 
 scalar_t__ __mf_starting_p ; 
 int /*<<< orphan*/  __mf_usage () ; 
 int __mfu_set_options (char*) ; 
 int /*<<< orphan*/  active ; 
 int /*<<< orphan*/  exit (int) ; 
 char* getenv (char*) ; 

void
__mf_init ()
{
  char *ov = 0;

  /* Return if initialization has already been done. */
  if (LIKELY (__mf_starting_p == 0))
    return;

  /* This initial bootstrap phase requires that __mf_starting_p = 1. */
#ifdef PIC
  __mf_resolve_dynamics ();
#endif
  __mf_starting_p = 0;

  __mf_set_state (active);

  __mf_set_default_options ();

  ov = getenv ("MUDFLAP_OPTIONS");
  if (ov)
    {
      int rc = __mfu_set_options (ov);
      if (rc < 0)
        {
          __mf_usage ();
          exit (1);
        }
    }

  /* Initialize to a non-zero description epoch. */
  __mf_describe_object (NULL);

#define REG_RESERVED(obj) \
  __mf_register (& obj, sizeof(obj), __MF_TYPE_NOACCESS, # obj)

  REG_RESERVED (__mf_lookup_cache);
  REG_RESERVED (__mf_lc_mask);
  REG_RESERVED (__mf_lc_shift);
  /* XXX: others of our statics?  */

  /* Prevent access to *NULL. */
  __mf_register (MINPTR, 1, __MF_TYPE_NOACCESS, "NULL");
  __mf_lookup_cache[0].low = (uintptr_t) -1;
}