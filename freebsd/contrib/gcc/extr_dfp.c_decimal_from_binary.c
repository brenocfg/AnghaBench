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
typedef  int /*<<< orphan*/  string ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  decimal_real_from_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  real_to_decimal (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
decimal_from_binary (REAL_VALUE_TYPE *to, const REAL_VALUE_TYPE *from)
{
  char string[256];

  /* We convert to string, then to decNumber then to decimal128.  */
  real_to_decimal (string, from, sizeof (string), 0, 1);
  decimal_real_from_string (to, string);
}