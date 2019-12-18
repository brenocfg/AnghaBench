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
typedef  TYPE_1__* optab ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_4__ {int code; } ;

/* Variables and functions */
 TYPE_1__* new_optab () ; 

__attribute__((used)) static inline optab
init_optabv (enum rtx_code code)
{
  optab op = new_optab ();
  op->code = code;
  return op;
}