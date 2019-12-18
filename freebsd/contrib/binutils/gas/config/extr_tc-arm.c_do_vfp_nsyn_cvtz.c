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
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  NS_FD ; 
 int /*<<< orphan*/  NS_FF ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  do_vfp_nsyn_opcode (char const*) ; 
 int neon_cvt_flavour (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_vfp_nsyn_cvtz (void)
{
  enum neon_shape rs = neon_select_shape (NS_FF, NS_FD, NS_NULL);
  int flavour = neon_cvt_flavour (rs);
  const char *enc[] =
    {
      "ftosizs",
      "ftouizs",
      NULL,
      NULL,
      NULL,
      NULL,
      "ftosizd",
      "ftouizd"
    };

  if (flavour >= 0 && flavour < (int) ARRAY_SIZE (enc) && enc[flavour])
    do_vfp_nsyn_opcode (enc[flavour]);
}