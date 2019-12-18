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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int DECL_CALL_CLOBBERED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTAG_P (int /*<<< orphan*/ ) ; 
 int bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_clobbered_vars ; 

__attribute__((used)) static inline bool
is_call_clobbered (tree var)
{
  if (!MTAG_P (var))
    return DECL_CALL_CLOBBERED (var);
  else
    return bitmap_bit_p (call_clobbered_vars, DECL_UID (var)); 
}