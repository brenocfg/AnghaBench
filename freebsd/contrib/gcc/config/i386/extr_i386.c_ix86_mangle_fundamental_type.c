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
#define  TFmode 129 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
#define  XFmode 128 

__attribute__((used)) static const char *
ix86_mangle_fundamental_type (tree type)
{
  switch (TYPE_MODE (type))
    {
    case TFmode:
      /* __float128 is "g".  */
      return "g";
    case XFmode:
      /* "long double" or __float80 is "e".  */
      return "e";
    default:
      return NULL;
    }
}