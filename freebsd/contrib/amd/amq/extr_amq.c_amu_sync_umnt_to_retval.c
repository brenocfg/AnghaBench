#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int au_etype; int /*<<< orphan*/  au_errno; } ;
typedef  TYPE_1__ amq_sync_umnt ;

/* Variables and functions */
#define  AMQ_UMNT_FORK 128 

__attribute__((used)) static int
amu_sync_umnt_to_retval(amq_sync_umnt *rv)
{
  switch (rv->au_etype) {
  case AMQ_UMNT_FORK:
    if (rv->au_errno == 0) {
      /*
       * We allow this error so that things like:
       *   amq -uu /l/cd0d && eject cd0
       * will work when /l/cd0d is not mounted.
       * XXX - We still print an error message.
       */
      return 0;
    }
    /*FALLTHROUGH*/
  default:
    return rv->au_etype;
  }
}