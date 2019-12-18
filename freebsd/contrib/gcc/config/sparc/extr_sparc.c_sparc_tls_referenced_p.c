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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_HAVE_TLS ; 
 int for_each_rtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc_tls_symbol_ref_1 ; 

bool
sparc_tls_referenced_p (rtx x)
{
  if (!TARGET_HAVE_TLS)
    return false;

  return for_each_rtx (&x, &sparc_tls_symbol_ref_1, 0);
}