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
typedef  scalar_t__ word ;
typedef  scalar_t__ byte ;
typedef  int /*<<< orphan*/  PLCI ;

/* Variables and functions */
 int /*<<< orphan*/  add_ie (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void add_p(PLCI   * plci, byte code, byte   * p)
{
  word p_length;

  p_length = 0;
  if(p) p_length = p[0];
  add_ie(plci, code, p, p_length);
}