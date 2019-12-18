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
struct TYPE_4__ {int sign; int canonical; int /*<<< orphan*/  cl; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvc_nan ; 

__attribute__((used)) static inline void
get_canonical_qnan (REAL_VALUE_TYPE *r, int sign)
{
  memset (r, 0, sizeof (*r));
  r->cl = rvc_nan;
  r->sign = sign;
  r->canonical = 1;
}